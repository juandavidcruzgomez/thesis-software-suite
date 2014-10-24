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
