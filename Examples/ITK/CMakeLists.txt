CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(ssm_itk)
SET(CMAKE_VERBOSE_MAKEFILE ON)

FIND_PACKAGE(STATISMO REQUIRED)

FIND_PACKAGE(ITK REQUIRED)
include (${ITK_USE_FILE})

SET (ITK_STATISTICAL_MODEL_INCLUDE_DIR ${STATISMO_DIR}/ITKstatismo)

FILE(GLOB INCLUDE_FILES *.h)
FILE(GLOB SOURCE_FILES  *.txx )

include_directories(${STATISMO_DIR} ${STATISMO_DIR}/statismo_ITK  ${STATISMO_INCLUDE_DIR}  ${ITK_INCLUDE_DIRS}  ${STATISMO_DIR}/Representers/ITK)
link_directories(${ITK_LIBRARY_DIRS} ${STATISMO_LIBRARY_DIR})

add_executable (buildDeformationModel buildDeformationModel.cpp 
	${SOURCE_FILES}
	${INCLUDE_FILES}
) 
target_link_libraries (buildDeformationModel ${ITK_LIBRARIES} ${STATISMO_LIBRARIES})

add_executable (deformationModelFitting deformationModelFitting.cpp 
	${SOURCE_FILES}
	${INCLUDE_FILES}
) 
target_link_libraries (deformationModelFitting  ${STATISMO_LIBRARIES} ${ITK_LIBRARIES})

add_executable (buildShapeModel buildShapeModel.cpp 
	${SOURCE_FILES}
	${INCLUDE_FILES}
) 
target_link_libraries (buildShapeModel ${ITK_LIBRARIES} ${STATISMO_LIBRARIES})


add_executable (shapeModelFitting shapeModelFitting.cpp 
	${SOURCE_FILES}
	${INCLUDE_FILES}
) 
target_link_libraries (shapeModelFitting  ${STATISMO_LIBRARIES} ${ITK_LIBRARIES})