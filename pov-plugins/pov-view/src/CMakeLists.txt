# Copyright (c) 2014 Juan David Cruz Gómez and Telecom - Bretagne
#
# juan.cruzgomez@telecom-bretagne.eu 
# juandavidcruz@gmail.com
#
# Licensed under the EUPL, Version 1.2 or – as soon theywill be approved 
# by the European Commission - subsequent versions of the 
# EUPL (the "Licence");
#
# You may not use this work except in compliance with the Licence.
# You may obtain a copy of the Licence at:
#
#    https://joinup.ec.europa.eu/software/page/eupl5
#  
# Unless required by applicable law or agreed to inwriting, software 
# distributed under the Licence isdistributed on an *"AS IS"* basis,
# *WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND*, either express or implied.
# See the Licence for the specific language governing permissions and limitations 
# under the Licence.
SET( CPP_FILES PoVViewPlugin.cpp
	MainWidgetView.cpp
	Controller.cpp
	Model.cpp
	SemanticPatternLoader.cpp
	PoVConfigurationView.cpp
	qcustomplot.cpp
	PoVLayoutDistortion.cpp
)

SET( MOC_HEADERS ../include/PoVViewPlugin.h
	../include/MainWidgetView.h
	../include/PoVConfigurationView.h
	../include/qcustomplot.h
)

SET( UI_FILES MainWidgetView.ui
	PatternLoadWindow.ui
)

SET( RESOURCE_FILES res/main_widget_res.qrc
)

QT4_WRAP_UI(UI_SRCS ${UI_FILES})
QT4_WRAP_CPP(MOC_SRCS ${MOC_HEADERS})
QT4_ADD_RESOURCES(RCC_SRCS ${RESOURCE_FILES})

ADD_LIBRARY(${PLUGIN_NAME}-${TULIP_PLUGIN_VERSION} SHARED ${CPP_FILES} ${UI_SRCS} ${MOC_SRCS} ${RCC_SRCS})

TARGET_LINK_LIBRARIES(${PLUGIN_NAME}-${TULIP_PLUGIN_VERSION} 
	${TULIP_LIBRARY} 
	${TULIP_QT4_LIBRARY} 
	${QT_LIBRARIES}
)

INSTALL( TARGETS ${PLUGIN_NAME}-${TULIP_PLUGIN_VERSION} LIBRARY DESTINATION ${TULIP_PLUGINS_PATH}/view )
