#clustering subdirectory

SET( HEADERS ${HEADERS}
             ${CMAKE_CURRENT_SOURCE_DIR}/louvain 
             ${CMAKE_CURRENT_SOURCE_DIR}/mixed 
             ${CMAKE_CURRENT_SOURCE_DIR}/centrality 
             ${CMAKE_CURRENT_SOURCE_DIR}/basicdm 
             ${CMAKE_CURRENT_SOURCE_DIR}/galoisclust
             ${CMAKE_CURRENT_SOURCE_DIR}/contingencyclust
             PARENT_SCOPE)
             
INCLUDE_DIRECTORIES( ${HEADERS} 
                  ${CMAKE_CURRENT_SOURCE_DIR}/louvain 
                  ${CMAKE_CURRENT_SOURCE_DIR}/mixed 
                  ${CMAKE_CURRENT_SOURCE_DIR}/centrality 
                  ${CMAKE_CURRENT_SOURCE_DIR}/basicdm
                  ${CMAKE_CURRENT_SOURCE_DIR}/galoisclust
                  ${CMAKE_CURRENT_SOURCE_DIR}/contingencyclust)

SET( CPP_FILES ${CPP_FILES}
  ${CMAKE_CURRENT_SOURCE_DIR}/clusteringbase.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tableclustering.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/utility.cpp)

ADD_SUBDIRECTORY( louvain )
ADD_SUBDIRECTORY( mixed )
ADD_SUBDIRECTORY( centrality )
ADD_SUBDIRECTORY( basicdm )
ADD_SUBDIRECTORY( galoisclust )
ADD_SUBDIRECTORY( contingencyclust )

INSTALL( FILES clusteringbase.h DESTINATION ${INSTALL_INCLUDE_PATH} )
INSTALL( FILES tableclustering.h DESTINATION ${INSTALL_INCLUDE_PATH} )
INSTALL( FILES colorwheel.h DESTINATION ${INSTALL_INCLUDE_PATH} )
INSTALL( FILES utility.h DESTINATION ${INSTALL_INCLUDE_PATH} )
