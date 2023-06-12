



streams_include_directories = include_directories('include')

streams_boost_modules = []

streams_boost_dep = dependency('boost',
                               required: true,
                               modules: streams_boost_modules)

streams_deps = [
    streams_boost_dep,
    csvparser_dep,
    sndfile_dep,
]


streams_sources = [
    'include/roughpy/streams/brownian_stream.h',
    'include/roughpy/streams/dyadic_caching_layer.h',
    'include/roughpy/streams/dynamically_constructed_stream.h',
    'include/roughpy/streams/external_data_stream.h',
    'include/roughpy/streams/lie_increment_stream.h',
    'include/roughpy/streams/piecewise_abelian_stream.h',
    'include/roughpy/streams/schema.h',
    'include/roughpy/streams/stream.h',
    'include/rougphy/streams/stream_base.h',
    'include/roughpy/streams/stream_construction_helper.h',
    'include/roughpy/streams/tick_stream.h',
    'src/external_data_sources/csv_data_source.cpp',
    'src/external_data_sources/csv_data_source.h',
    'src/external_data_sources/sound_file_data_source.cpp',
    'src/external_data_sources/sound_file_data_source.h',
    'src/brownian_stream.cpp',
    'src/dyadic_caching_layer.cpp',
    'src/dynamically_constructed_stream.cpp',
    'src/external_data_stream.cpp',
    'src/lie_increment_stream.cpp',
    'src/piecewise_abelian_stream.cpp',
    'src/schema.cpp',
    'src/stream.cpp',
    'src/stream_base.cpp',
    'src/stream_construction_helper.cpp'
]

streams_links = [
    core_lib,
    platform_lib,
    scalars_lib,
    intervals_lib,
    algebra_lib
]


streams_lib = library('roughpy_streams', streams_sources,
                      include_directories: streams_include_directories,
                      link_with: streams_links,
                      dependencies: streams_deps,
                      pic: true)


streams_tests = executable('streams_tests',
                           'src/test_brownian_stream.cpp',
                           'src/test_lie_increment_stream.cpp',
                           'src/test_schema.cpp',
                           'src/tick_stream.cpp',
                           link_with: streams_lib,
                           install: false)
test('streams_tests', streams_tests)
