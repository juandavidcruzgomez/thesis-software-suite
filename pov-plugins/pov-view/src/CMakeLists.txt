#The MIT License (MIT)

#Copyright (c) 2012 Juan David Cruz Gómez and Telecom - Bretagne
#juan.cruzgomez@telecom-bretagne.eu

#Permission is hereby granted, free of charge, to any person obtaining a copy
#of this software and associated documentation files (the "Software"), to deal
#in the Software without restriction, including without limitation the rights
#to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#copies of the Software, and to permit persons to whom the Software is
#furnished to do so, subject to the following conditions:

#The above copyright notice and this permission notice shall be included in
#all copies or substantial portions of the Software.

#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#THE SOFTWARE.
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
