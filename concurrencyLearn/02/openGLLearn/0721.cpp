#include <GLFW/glfw3.h>
#include <iostream>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);//使用的Opengl的主要版本
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);//次要版本
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//opengl的模式是核心模式
  
  //创建窗口对象（object）,这个窗口对象存放了所有和窗口相关的数据，而且会被GLFW的其他函数频繁用到
  GLFWwindow* window = glfwCreateWindow(800,600,"LearnOpenGL",NULL,NULL);
  if(NULL==window)
  {
    std::cout<<"Failed to create GLFW window"<<std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);//将窗口的上下文设置为当前线程的主上下文
  glViewport(0,0,800,600);
  glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
  while(!glfwWindowShouldClose(window))//检查glfw是否被要求退出
  {
    //输入
    processInput(window);
    //渲染指令
    glClearColor(0.2f,0.3f,0.3f,1.0f);//这是一个状态设置函数，而glClear函数则是一个状态使用函数，它使用了当前的状态来获取应该清除为的颜色
    glClear(GL_COLOR_BUFFER_BIT);
    
    glfwSwapBuffers(window);//交换颜色缓冲
    glfwPollEvents();//检查有没有触发什么事件（如键盘输入，鼠标移动等），更新窗口状态
    //并调用对应的回调函数（可以通过回调函数方法手动设置）
    
  }
  glfwTerminate();//正确释放，删除之前的分配的所有资源
  return 0;
  
}
//设置回调函数，当窗口尺寸变化的时候，对应的viewPort也会变化，当窗口第一次显示的时候，这个回调函数
//也会被调用，但是需要使用函数注册一下： 
//glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
//回调函数，还可以被设计注册到其他很多的回调函数中，比如说，可以创建一个回调函数
//处理手柄输入变化，处理错误消息等，在创建窗口之后，渲染循环初始化之前注册这些回调函数

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0,0,width,height);
}

void processInput(GLFWwindow* window)
{
  if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window,true);
  }
}

/*
int main()
{
  GLFWwindow* window;
  if(!glfwInit())
    return -1;
  window = glfwCreateWindow(640,480,"Hello Opengl",NULL,NULL);
  if(!window)
  {
    glfwTerminate();
    return -1;
  }
  while(!glfwWindowShouldClose(window))
  {
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;  
}*/



//CMakeLists.txt
cmake_minimum_required(VERSION 2.8)
PROJECT(OPENGL_LEARN_1)


#find_package(GLUT REQUIRED)
#include_directories(${GLUT_INCLUDE_DIRS})
#link_directories(${GLUT_LIBRARY_DIRS})
#add_definitions(${GLUT_DEFINITIONS})
#if(NOT GLUT_FOUND)
#    message(ERROR " GLUT not found!")
#endif(NOT GLUT_FOUND)

#find_package(glfw3 REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3 dl)
include_directories(
        ${GLFW_INCLUDE_DIRS}
)
link_directories(${GLFW_LIBRARY_DIRS})
add_definitions(${GLFW_DEFINITIONS})

find_package(X11 REQUIRED)
#find_package(PTHREAD REQUIRED)
find_package(Threads)



find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)




add_executable(test main.cpp)
target_link_libraries(test ${OPENGL_LIBRARIES} ${GLUT_glut_LIBRARY} ${GLFW_LIBRARIES} ${X11_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} /usr/lib/x86_64-linux-gnu/libdl.so)
#target_link_libraries(test ${OPENGL_LIBRARIES} ${GLUT_glut_LIBRARY} ${GLFW_LIBRARIES}  ${X11_Xrandr_LIB} 
#${X11_Xi_LIB} ${X11_Xrender_LIB} ${X11_Xdamage_LIB} ${X11_Xxf86vm_LIB} ${X11_Xext_LIB}  ${X11_X11_LIB} ${X11_Xinerama_LIB} ${X11_Xcursor_LIB} )
