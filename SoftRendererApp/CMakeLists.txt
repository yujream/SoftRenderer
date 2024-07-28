# CMakeList.txt: SoftRendererApp 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

project(SoftRendererApp)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 如果没有指定路径，则使用全局
# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)

if (MSVC)
	set(QT_VERSION_MAJOR 6)
	add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

set(QT_PREFIX_PATH "D:/Qt/6.7.2/msvc2019_64")
set(CMAKE_PREFIX_PATH ${QT_PREFIX_PATH})

include_directories(
	${QT_PREFIX_PATH}/include
	${CMAKE_CURRENT_SOURCE_DIR}/include
	"../submodules/MathUtils/include"
)

# 查找 QT 依赖包
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Gui REQUIRED)

file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} form/*.ui)
file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resources/*.qrc)
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} include/*.h)
file(GLOB_RECURSE PROJECT_SOURCES RELATIE ${CMAKE_CURRENT_SOURCE_DIR} source/*.cpp)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
	QT6_ADD_RESOURCES(QT_RESOURCES_FILES ${QT_RESOURCES})
	QT6_WRAP_UI(QT_FORMS_FILES ${QT_FORMS})
	QT6_WRAP_CPP(QT_MOC_FILES ${QT_MOC})
	qt_add_executable(SoftRendererApp
		# MANUAL_FINALIZATION # 带控制台
		WIN32
		${QT_RESOURCES_FILES}
		${QT_MOC_FILES}
		${QT_FORMS_FILES}
		${PROJECT_SOURCES}
	)
else()
	QT5_ADD_RESOURCES(QT_RESOURCES_FILES ${QT_RESOURCES})
	QT5_WRAP_UI(QT_FORMS_FILES ${QT_FORMS})
	QT5_WRAP_CPP(QT_MOC_FILES ${QT_MOC})
	add_executable(SoftRendererApp
		WIN32
		${QT_RESOURCES_FILES}
		${QT_MOC_FILES}
		${QT_FORMS_FILES}
		${PROJECT_SOURCES}
	)
endif()

# 添加 QT 依赖
target_link_libraries(SoftRendererApp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui)

# 添加子模块依赖
target_link_libraries(SoftRendererApp PRIVATE MathUtils)

if(QT_VERSION_MAJOR EQUAL 6)
	qt_finalize_executable(SoftRendererApp)
endif()

# 第三方库
include_directories(
	"../3rd/eigen3"
	"../3rd/stb"
)

# 拷贝资源文件
file(GLOB copyResources "../assets")
file(COPY ${copyResources} DESTINATION ${CMAKE_BINARY_DIR})

# 确定架构
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH_DIR "x64")
else()
    set(ARCH_DIR "x86")
endif()

# 设置可执行程序输出路径
set_target_properties(SoftRendererApp PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/bin/${ARCH_DIR}/${CMAKE_BUILD_TYPE}")
