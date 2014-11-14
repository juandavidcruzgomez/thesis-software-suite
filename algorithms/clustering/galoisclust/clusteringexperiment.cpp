/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2014  <copyright holder> <email>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


#include "clusteringexperiment.h"

ClusteringExperiment::ClusteringExperiment(Graph* _theGraph, string patterns_filename, string global_name)
  :	theGraph(_theGraph)
{
  pattern_property = "data_vector";
  experiment_name = global_name;
  import = new ImportBase( theGraph, pattern_property );
  import->set_filename( patterns_filename );
  ground_truth = 0;
}

ClusteringExperiment::~ClusteringExperiment()
{
  if( lattice != 0 )
  {
    delete lattice;
    lattice = 0;
  }
  if( cmat != 0 )
  {
    delete cmat;
    cmat = 0;
  }
  if( import != 0 )
  {
    delete import;
    import = 0;
  }
  map<int, ClusteringBase*>::iterator experiments_map_iter;
  for( experiments_map_iter = experiments_map.begin(); experiments_map_iter != experiments_map.end(); experiments_map_iter++ )
  {
    delete experiments_map_iter->second;
  }
  experiments_map.clear();
  map<int, BasicEntropy*>::iterator sub_groups_ent_map_iter;
  for( sub_groups_ent_map_iter = sub_groups_ent_map.begin(); sub_groups_ent_map_iter != sub_groups_ent_map.end(); sub_groups_ent_map_iter++ )
  {
    delete sub_groups_ent_map_iter->second;
  }
  sub_groups_ent_map.clear();
}

void ClusteringExperiment::import_patterns()
{
  import->read_file( 1 );
}

void ClusteringExperiment::add_experiment( string experiment_name, int type )
{
  int actual_experiment_id = experiments_map.size();
  experiments_name_map[actual_experiment_id] = experiment_name;
  sub_groups_map[actual_experiment_id] = theGraph->addCloneSubGraph();
  sub_groups_ent_map[actual_experiment_id] = new BasicEntropy( sub_groups_map[actual_experiment_id], pattern_property );
  experiments_done[actual_experiment_id] = false;
  switch( type )
  {
    case( LOUVAIN ):
    {
      experiments_map[actual_experiment_id] = new Louvain( sub_groups_map[actual_experiment_id], 250, 10E-5, "structural" );
    }
      break;
    case( POV ):
    {
      experiments_map[actual_experiment_id] = new PoVClustering( sub_groups_map[actual_experiment_id], 250, 10E-5, "mixed_partition", pattern_property );
    }
      break;
    case( KMEANS ):
    {
      experiments_map[actual_experiment_id] = new GeneralKMeans( sub_groups_map[actual_experiment_id], 100, 1E-5, "kmeans_based", pattern_property, 64 );
    }
      break;
    case( GALOIS ):
    {
      if( lattice != 0 )
      {
	lattice->generate_lattice();
	LatticeExporter expo( lattice );
	string lattice_name = experiment_name;
	lattice_name.append("_lattice.txt");
	expo.export_lattice(lattice_name);
	experiments_map[actual_experiment_id] = new BasicGaloisClustering( lattice, sub_groups_map[actual_experiment_id], 100, 1E-5, "GaloisBased");
      }else{
	cerr << "The Galois lattice based algorithm cannot be executed because the lattice could not be instantiated." << endl;
      }
    }
      break;
    default:
      cerr << "Clustering algorithm not defined." << endl;
      assert(false);
      break;
  }
}

void ClusteringExperiment::start_resgistered_experiments( ostream& os )
{
  map<int, ClusteringBase*>::iterator experiments_iter;
  for( experiments_iter = experiments_map.begin(); experiments_iter != experiments_map.end(); experiments_iter++ )
  {
    if( !experiments_done[experiments_iter->first] ){
      os << "Executing experiment " << experiments_name_map[experiments_iter->first] << "..." << endl;
      experiments_iter->second->execute_algorithm();
      experiments_done[experiments_iter->first] = true;
      os << "Experiment " << experiments_name_map[experiments_iter->first] << " is done." << endl;
    }else{
      cerr << "The experiment " << experiments_name_map[experiments_iter->first] << " was already done... " << endl;
    }
  }
}

void ClusteringExperiment::calculate_statistics( ostream& os )
{
  // Entropy
  map<int, BasicEntropy*>::iterator entropy_iterator;
  for( entropy_iterator = sub_groups_ent_map.begin(); entropy_iterator != sub_groups_ent_map.end(); ++entropy_iterator )
  {
    os << "Stats for the group " << experiments_name_map[entropy_iterator->first] << ": " << endl;
    double ent = entropy_iterator->second->calculatePartitionEntropy();
    float dens = edge_density( sub_groups_map[entropy_iterator->first] );      
    os << "Entropy: " << ent <<  endl;
    os << "Density: " << dens << endl;
    os << "Number of groups: " << sub_groups_map[entropy_iterator->first]->numberOfSubGraphs() << endl;
    os << "--------------------------------------------------" << endl;
  }
  double ari = 0.0;
  for( unsigned int i = 0; i < experiments_name_map.size(); ++i )
  {
    for( unsigned int j = 0; j < experiments_name_map.size(); ++j )
    {
      ari = calculate_ARI( sub_groups_map[i], sub_groups_map[j] );
      os << "ARI between "<< experiments_name_map[i] << " and " << experiments_name_map[j] << ": "<< ari << endl;
    }
  }
}

void ClusteringExperiment::calculate_against_ground_truth( ostream& os )
{
  if( ground_truth != 0 )
  {
    os << "------ CALCULATING GROUND TRUTH VALUES ------" << endl;
    double ari = 0.0;
    for( unsigned int i = 0; i < experiments_name_map.size(); ++i )
    {
      ari = calculate_ARI( ground_truth, sub_groups_map[i] );
      os << "ARI between GT and " << experiments_name_map[i] << " is: "<< ari << endl;
    }
  }else{
    os << "The ground truth cannot be calculated because there isn't any..." << endl;
  }
}

void ClusteringExperiment::initialize_lattice( Matrix* composition_matrix, int structural_index )
{
  assert( composition_matrix != 0 && structural_index >= 0 );
  cmat = new ConceptMatrix();
  int rows = theGraph->numberOfNodes();
  int lcols = sub_groups_map[structural_index]->numberOfSubGraphs();
  if( lcols == 0 )
  {
    experiments_map[structural_index]->execute_algorithm();
    experiments_done[structural_index] = true;
    lcols = sub_groups_map[structural_index]->numberOfSubGraphs();
  }
  assert( lcols > 0 );
  Matrix* structural_aff_mat = new Matrix(rows,lcols,COLUMN_MAJOR);
  get_affiliation_matrix( structural_aff_mat, sub_groups_map[structural_index] );
  Matrix* concatenation = structural_aff_mat->column_rconcatenate( composition_matrix );
  populate_object_attr_matrix( cmat, concatenation );
  cmat->add_attribute_limit( lcols );
  lattice = new GaloisLattice( cmat );
  //Clean the mess up
  delete concatenation;
  delete structural_aff_mat;
}

void ClusteringExperiment::set_ground_truth( Matrix* _ground_truth )
{
  assert( _ground_truth != 0 );
  ground_truth = _ground_truth;
}