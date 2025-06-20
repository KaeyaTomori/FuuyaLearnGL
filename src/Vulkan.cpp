#include "Vulkan.h"


//-------------------vulkan-------------------------------
// #define GLFW_INCLUDE_VULKAN
// #include <GLFW/glfw3.h>
//
// #include <iostream>
// #include <stdexcept>
// #include <cstdlib>
// #include <vector>
// #include <optional>
//
// const uint32_t WIDTH = 800;
// const uint32_t HEIGHT = 600;
//
// const std::vector<const char*> validationLayers = {
//     "VK_LAYER_KHRONOS_validation"
// };
//
// #ifdef NDEBUG
// const bool enableValidationLayers = false;
// #else
// const bool enableValidationLayers = true;
// #endif
//
// class HelloTriangleApplication {
// public:
//     void run() {
//         initWindow();
//         initVulkan();
//         mainLoop();
//         cleanup();
//     }
//
// private:
//     void initWindow() {
//         glfwInit();
//         
//         // 不创建openGL上下文
//         glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
//         glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
//         
//         window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
//         
//     }
//
//     void createSurface()
//     {
//         if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
//             throw std::runtime_error("failed to create window surface!");
//         }
//     }
//
//     void initVulkan() {
//         createInstance();
//         setupDebugCallback();
//         createSurface();
//         pickPhysicalDevice();
//         createLogicalDevice();
//     }
//
//     void createLogicalDevice() {
//         QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
//
//         VkDeviceQueueCreateInfo queueCreateInfo = {};
//         queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
//         queueCreateInfo.queueFamilyIndex = indices.graphicsFamily;
//         queueCreateInfo.queueCount = 1;
//         float queuePriority = 1.0f;
//         queueCreateInfo.pQueuePriorities = &queuePriority;
//
//         VkPhysicalDeviceFeatures deviceFeatures = {};
//         VkDeviceCreateInfo createInfo = {};
//         createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
//         createInfo.pQueueCreateInfos = &queueCreateInfo;
//         createInfo.queueCreateInfoCount = 1;
//
//         createInfo.pEnabledFeatures = &deviceFeatures;
//
//         createInfo.enabledExtensionCount = 0;
//
//         if (enableValidationLayers) {
//             createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
//             createInfo.ppEnabledLayerNames = validationLayers.data();
//         } else {
//             createInfo.enabledLayerCount = 0;
//         }
//
//         if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
//             throw std::runtime_error("failed to create logical device!");
//         }
//
//         vkGetDeviceQueue(device, indices.graphicsFamily(), 0, &graphicsQueue);
//     }
//     
//     void createInstance()
//     {
//         VkApplicationInfo appInfo{};
//         appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
//         appInfo.pApplicationName = "Hello Triangle";
//         appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
//         appInfo.pEngineName = "No Engine";
//         appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
//         appInfo.apiVersion = VK_API_VERSION_1_0;
//
//         if (enableValidationLayers && !checkValidationLayerSupport()) {
//             throw std::runtime_error("validation layers requested, but not available!");
//         }
//         VkInstanceCreateInfo createInfo{};
//         createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
//         createInfo.pApplicationInfo = &appInfo;
//
//         auto extensions = getRequiredExtensions();
//         createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
//         createInfo.ppEnabledExtensionNames = extensions.data();
//         
//         if (enableValidationLayers) {
//             createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
//             createInfo.ppEnabledLayerNames = validationLayers.data();
//         } else {
//             createInfo.enabledLayerCount = 0;
//         }
//         
//         if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
//             throw std::runtime_error("failed to create instance!");
//         }
//     }
//
//     void pickPhysicalDevice() {
//         uint32_t deviceCount = 0;
//         vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
//         if (deviceCount == 0)
//         {
//             throw std::runtime_error("failed to find GPUs with Vulkan support!");
//         }
//
//         std::vector<VkPhysicalDevice> devices(deviceCount);
//         vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
//
//         for (const auto& device : devices) {
//             if (isDeviceSuitable(device)) {
//                 physicalDevice = device;
//                 break;
//             }
//         }
//
//         if (physicalDevice == VK_NULL_HANDLE) {
//             throw std::runtime_error("failed to find a suitable GPU!");
//         }
//
//         
//     }
//
//     bool isDeviceSuitable(VkPhysicalDevice device) {
//         // VkPhysicalDeviceProperties deviceProperties;
//         // vkGetPhysicalDeviceProperties(device, &deviceProperties);
//         // VkPhysicalDeviceFeatures deviceFeatures;
//         // vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
//         // return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
//         //    deviceFeatures.geometryShader;
//
//         QueueFamilyIndices indices = findQueueFamilies(device);
//
//         return indices.isComplete();
//
//     }
//     
//     struct QueueFamilyIndices {
//         int graphicsFamily = -1;
//         int presentFamily = -1;
//
//         bool isComplete() {
//             return graphicsFamily >= 0 && presentFamily >= 0;
//         }
//     };
//
//     QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
//         QueueFamilyIndices indices;
//         // Logic to find queue family indices to populate struct with
//         uint32_t queueFamilyCount = 0;
//         vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
//
//         std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
//         vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
//
//         
//         int i = 0;
//         for (const auto& queueFamily : queueFamilies) {
//             // if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
//             //     indices.graphicsFamily = i;
//             // }
//             VkBool32 presentSupport = false;
//             vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
//             if (queueFamily.queueCount > 0 && presentSupport) {
//                 indices.presentFamily = i;
//             }
//             
//             if (indices.isComplete()) {
//                 break;
//             }
//             
//             i++;
//         }
//         return indices;
//     }
//     
//     void mainLoop() {
//         while (!glfwWindowShouldClose(window)) {
//             glfwPollEvents();
//         }
//     }
//
//     void cleanup() {
//         vkDestroyDevice(device, nullptr);
//         
//         DestroyDebugReportCallbackEXT(instance, callback, nullptr);
//
//         vkDestroySurfaceKHR(instance, surface, nullptr);
//         vkDestroyInstance(instance, nullptr);
//         
//         glfwDestroyWindow(window);
//
//         glfwTerminate();
//     }
//
//     bool checkValidationLayerSupport() {
//         uint32_t layerCount;
//         vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
//
//         std::vector<VkLayerProperties> availableLayers(layerCount);
//         vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
//
//         for (const char* layerName : validationLayers) {
//             bool layerFound = false;
//
//             for (const auto& layerProperties : availableLayers) {
//                 if (strcmp(layerName, layerProperties.layerName) == 0) {
//                     layerFound = true;
//                     break;
//                 }
//             }
//
//             if (!layerFound) {
//                 return false;
//             }
//         }
//
//         return true;
//     }
//
//     std::vector<const char*> getRequiredExtensions() {
//         std::vector<const char*> extensions;
//
//         unsigned int glfwExtensionCount = 0;
//         const char** glfwExtensions;
//         glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
//
//         for (unsigned int i = 0; i < glfwExtensionCount; i++) {
//             extensions.push_back(glfwExtensions[i]);
//         }
//
//         if (enableValidationLayers) {
//             extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
//         }
//
//         return extensions;
//     }
//
//     void setupDebugCallback() {
//         if (!enableValidationLayers) return;
//
//         VkDebugReportCallbackCreateInfoEXT createInfo = {};
//         createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
//         createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
//         createInfo.pfnCallback = debugCallback;
//
//         if (CreateDebugReportCallbackEXT(instance, &createInfo, nullptr, &callback) != VK_SUCCESS) {
//             throw std::runtime_error("failed to set up debug callback!");
//         }
//     }
//
//     void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator) {
//         auto func = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
//         if (func != nullptr) {
//             func(instance, callback, pAllocator);
//         }
//     }
//
//     VkResult CreateDebugReportCallbackEXT(  VkInstance instance,
//                                             const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
//                                             const VkAllocationCallbacks* pAllocator,
//                                             VkDebugReportCallbackEXT* pCallback) {
//         auto func = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
//         if (func != nullptr) {
//             return func(instance, pCreateInfo, pAllocator, pCallback);
//         } else {
//             return VK_ERROR_EXTENSION_NOT_PRESENT;
//         }
//     }
//
//     static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
//         VkDebugReportFlagsEXT flags,
//         VkDebugReportObjectTypeEXT objType,
//         uint64_t obj,
//         size_t location,
//         int32_t code,
//         const char* layerPrefix,
//         const char* msg,
//         void* userData) {
//
//         std::cerr << "validation layer: " << msg << std::endl;
//
//         return VK_FALSE;
//     }
// private:
//     GLFWwindow* window;
//     VkInstance instance;
//     VkDebugReportCallbackEXT callback;
//     VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
//     VkDevice device;
//     VkQueue graphicsQueue;
//     VkSurfaceKHR surface;
//     VkQueue presentQueue;
// };
//
// int main() {
//     HelloTriangleApplication app;
//
//     try {
//         app.run();
//     } catch (const std::exception& e) {
//         std::cerr << e.what() << std::endl;
//         return EXIT_FAILURE;
//     }
//
//     return EXIT_SUCCESS;
// }