file(GLOB DDS_HELLOWORLD_SOURCES_CXX "*.cxx")

add_executable(DDSHelloWorldPublisher HelloWorldPublisher.cpp ${DDS_HELLOWORLD_SOURCES_CXX})
target_link_libraries(DDSHelloWorldPublisher fastdds fastcdr)

add_executable(DDSHelloWorldSubscriber HelloWorldSubscriber.cpp ${DDS_HELLOWORLD_SOURCES_CXX})
target_link_libraries(DDSHelloWorldSubscriber fastdds fastcdr)