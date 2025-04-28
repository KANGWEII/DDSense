add_subdirectory(foonathan_memory_vendor)
add_subdirectory(Fast-CDR)
add_subdirectory(Fast-DDS)

if (FAST_DDS_SAMPLE)
    add_subdirectory(sample)
endif ()