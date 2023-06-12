

intervals_include_directories = include_directories('include')

intervals_deps = []


intervals_sources = [
    'include/roughpy/intervals/dyadic.h',
    'include/roughpy/intervals/dyadic_interval.h',
    'include/roughpy/intervals/interval.h',
    'include/roughpy/intervals/real_interval.h',
    'include/roughpy/intervals/segmentation.h',
    'src/dyadic.cpp',
    'src/dyadic_interval.cpp',
    'src/dyadic_searcher.cpp',
    'src/dyadic_searcher.h',
    'src/interval.cpp',
    'src/real_interval.cpp',
    'src/scaled_predicate.cpp',
    'src/scaled_predicate.h',
    'src/segmentation.cpp'
]


intervals_lib = library('roughpy_intervals', intervals_sources,
                        include_directories: intervals_include_directories,
                        dependencies: intervals_deps,
                        link_with: [core_lib, platform_lib],
                        pic: true)



intervals_tests_exe = executable('roughpy_intervals_tests',
                                 'src/test_dyadic.cpp',
                                 'src/test_dyadic_intervals.cpp',
                                 'src/test_real_interval.cpp',
                                 install: false,
                                 link_with: intervals_lib,
                                 include_directories: intervals_include_directories,
                                 dependencies: [gtest_dep]
                                 )
test('intervals tests', intervals_tests_exe)
