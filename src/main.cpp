#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std; 

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

std::vector<int> bubbleSort(std::vector<int> v);

int main()
{
    if (!glfwInit())
    {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
    window = glfwCreateWindow(800, 600, "Algorithm Visualiser", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to open GLFW window" << endl;
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    //  Generating random vector 
    std::random_device rd;
    std::mt19937 gen(rd());         // Mersenne Twister engine
    std::uniform_int_distribution<> dist(1, 50);

    std::vector<int> data(8);
    std::generate(data.begin(), data.end(), [&](){ return dist(gen); });
    sortState = {};

    struct BubbleSortState {
        size_t i = 0, j = 0;
        bool swappedInPass = false;
        bool done = false;
        void step(std::vector<int>& a) {
            if (done || a.empty()) return;
            if(i >= a.size()){ done = true; return;}

            if (j + 1 < a.size() - i) {
                if (a[j] > a[j + 1]) {
                    std::swap(a[j], a[j + 1]);
                    swappedInPass = true;
                }
                ++j;
            } else {
                if (!swappedInPass) { done = true; return; }
                swappedInPass = false;
                j = 0;
                ++i;
            }
        }
    } sortState;

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while(!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}