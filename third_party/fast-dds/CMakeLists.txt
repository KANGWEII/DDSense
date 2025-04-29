if (BUILD_FAST_DEPENDENCIES)
    add_subdirectory(foonathan_memory_vendor)
    add_subdirectory(Fast-CDR)
endif()

if (BUILD_FAST_DDS)
    add_subdirectory(Fast-DDS)
endif()

if (FAST_DDS_SAMPLE)
    add_subdirectory(sample)
endif()