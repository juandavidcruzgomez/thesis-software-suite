#include <iostream>
#include <time.h>

#include <tulip/Graph.h>

#include "CLayoutSpace.h"

#include "Matrix.h"
#include "basicoperations.h"
#include "multidimscaling.h"

using namespace std;
using namespace tlp; 

void testMatrixCreation(){
	float data1[] = {1,2,3,4,5,6,7,8,9,10,
	1,2,3,4,5,6,7,8,9,10,
	1,2,3,4,5,6,7,8,9,10,
	1,2,3,4,5,6,7,8,9,10,
	1,2,3,4,5,6,7,8,9,10,
	1,2,3,4,5,6,7,8,9,10,
	1,2,3,4,5,6,7,8,9,10,
	1,2,3,4,5,6,7,8,9,10,
	1,2,3,4,5,6,7,8,9,10,
	1,2,3,4,5,6,7,8,9,10};
	float data2[] = {1,2,3,4,5,
	6,7,8,9,0,
	1,2,3,4,5,
	6,7,8,9,0,
	1,2,3,4,5};
	float data3[] = {0,2,4,6,8,10,12,14,16,18,
	1,3,5,7,9,11,13,15,19,21,
	0,2,4,6,8,10,12,14,16,18,
	1,3,5,7,9,11,13,15,19,21,
		0,2,4,6,8,10,12,14,16,18};
	//First,if create two matrices of nxn elements, then multiply them.
	int n1 = 10;
	int n2 = 5;
	Matrix* mat1 = new Matrix(n1,n1,COLUMN_MAJOR);
	mat1->setPdmatrix(data1);
	Matrix* mat2 = new Matrix(n1,n1,COLUMN_MAJOR);
	mat2->setPdmatrix(data1);
	cout << "There are " << Matrix::counter << " matrices." << endl;
	cout << "Matrix A: \n";
	mat1->printMatrix();
	cout << "Matrix B: \n";
	mat2->printMatrix();
	
	Matrix* mat3 = new Matrix(n1,n1,COLUMN_MAJOR);
	mat_mult_float(CBlas, n1, n1, n1, mat1->getPdmatrix(), mat2->getPdmatrix(), mat3->getPdmatrix(), 1, 0);
	cout << "Matrix C: \n";
	mat3->printMatrix();
	//Second, using the same space, create two matrices of (n/2)x(n/2), then multiply them and see what happens.
	mat1->recycleMatrixSpace(n2, n1,data3);
	cout << "Matrix Ar: \n";
	mat1->printMatrix();
	mat2->recycleMatrixSpace(n1, n2,data3);
	cout << "Matrix Br: \n";
	mat2->printMatrix();
	mat3->recycleMatrixSpace(n2, n2);
	mat_mult_float(CBlas, n2, n2, n1, mat1->getPdmatrix(), mat2->getPdmatrix(), mat3->getPdmatrix(), 1, 0);
	cout << "Matrix C: \n";
	mat3->printMatrix();
	//Delete used memory
	delete mat1;
	cout << "There are " << Matrix::counter << " matrices." << endl;
	delete mat2;
	cout << "There are " << Matrix::counter << " matrices." << endl;
	delete mat3;
	cout << "There are " << Matrix::counter << " matrices." << endl;
}

void multidimscalingTest(){
	float data1[] = {0,2,3,4,5,6,7,8,9,10,
		1,0,3,4,5,6,7,8,9,10,
		1,2,0,4,5,6,7,8,9,10,
		1,2,3,0,5,6,7,8,9,10,
		1,2,3,4,0,6,7,8,9,10,
		1,2,3,4,5,0,7,8,9,10,
		1,2,3,4,5,6,0,8,9,10,
		1,2,3,4,5,6,7,0,9,10,
		1,2,3,4,5,6,7,8,0,10,
		1,2,3,4,5,6,7,8,9,0};
	float data2[] = {0,1,1,1,1,
	1,0,1,1,1,
	1,1,0,1,1,
	1,1,1,0,1,
	1,1,1,1,0};
	int n1 = 10;
	int n2 = 5;
	Matrix* dissmat = new Matrix( n1,n1, COLUMN_MAJOR );
	dissmat->setPdmatrix(data1);
	cout << "Dissimilarity matrix: " << endl;
	dissmat->printMatrix();
	MDS_space* space = new MDS_space(n1,dissmat);
	space->calculate_initial_points();
	space->start_mds(250, 1E-5);
	cout << "Points:" << endl;
	space->get_z_matrix()->printMatrix();
	//Recycle
	dissmat->recycleMatrixSpace(n2, n2, data2);
	space->recycle_mds_space(n2);
	space->calculate_initial_points();
	space->start_mds(250, 1E-5);
	cout << "Recycled points:" << endl;
	space->get_z_matrix()->printMatrix();
	delete dissmat;
	delete space;
}

int main(int argc, char **argv) {
	//Playground tests
	//testMatrixCreation();
	//multidimscalingTest();
	
    //char graphfilename[] = {"/Users/juandavidcruz/Documents/workspace/tulip_standalone/CommunityVisualizationV2/personalNetwork.tlp"};
    //char graphfilename[] = {"/home/juancrug/workspace/software/tulip_standalone/CommunityVisualization/telecom_musical_tests.tlp"};
	char graphfilename[] = {"/Users/juandavidcruz/Documents/workspace/tulip_standalone/CommunityVisualization/arxiv_grouped.tlp"};
    
    //char dest_graphfilename[] = {"/Users/juandavidcruz/Documents/workspace/tulip_standalone/CommunityVisualizationV2/personalNetwork_layout.tlp"};
    //char dest_graphfilename[] = {"/home/juancrug/workspace/software/tulip_standalone/CommunityVisualization/telecom_musical_tests_layout.tlp"};
	char dest_graphfilename[] = {"/Users/juandavidcruz/Documents/workspace/tulip_standalone/CommunityVisualization/arxiv_grouped_layout.tlp"};
	
    Graph* theGraph = NULL;
    
    theGraph = tlp::loadGraph(graphfilename);
    if( theGraph != NULL ){
      long init_time = clock();
      CLayoutSpace layoutSpace(theGraph);
      long end_time = clock();
      cout << "Algorithm initialization time: " << (float)(end_time-init_time)/CLOCKS_PER_SEC << " seconds\n";
      layoutSpace.startAlgorithm(true);
      LayoutProperty *layout = theGraph->getProperty<LayoutProperty>("viewLayout");
      Iterator<node> *nodeIter = theGraph->getNodes();
      while( nodeIter->hasNext() ){
	      node n = nodeIter->next();
	      Coord c  = layoutSpace.getPositions()[n];
	      c.setX(c.getX()*1600.0f);
	      c.setY(c.getY()*1600.0f);
	      layout->setNodeValue(n, c );
      }
      
      
      tlp::saveGraph(theGraph,dest_graphfilename);
      /*if( theGraph != NULL ){
	delete theGraph;
      }*/
    }else{
      cout << "Error loading the graph...\n";
    }
    return 0;
}
