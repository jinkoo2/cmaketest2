#include <iostream>
#include <GLFW/glfw3.h>
#include <cmaketest2Config.h>

#ifdef USE_MATH
    #include <add.h>
#endif

int main(int argc, char* argv[]){
    
#ifdef USE_MATH
    std::cout << "Hey! " << add(1,2) << std::endl;
#endif

    std::cout << argv[0] << " Version " << cmaketest2_VERSION_MAJOR << "." << cmaketest2_VERSION_MINOR <<std::endl;

#ifdef USE_MATH
    std::cout<< "USE_MATH defined!" <<std::endl;
#else
    std::cout<< "USE_MATH not defined!" <<std::endl;
#endif /* USE_MATH */

    GLFWwindow* window;
    int width, height;

    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }

    glfwWindowHint(GLFW_DEPTH_BITS, 16);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    window = glfwCreateWindow( 300, 300, "Gears", NULL, NULL );
    if (!window)
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

// Main loop
    while( !glfwWindowShouldClose(window) )
    {

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}