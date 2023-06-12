
core_sources = [
    'include/roughpy/core/alloc.h',
    'include/roughpy/core/helpers.h',
    'include/roughpy/core/macros.h',
    'include/roughpy/core/slice.h',
    'include/roughpy/core/traits.h',
    'include/roughpy/core/types.h'
]
core_include_directories = include_directories('include')

core_boost_dep = dependency('boost', required: true,
                            modules: ['alignment', 'type_traits', 'predef'])

core_lib = library('roughpy_core', core_sources,
                    include_directories: core_include_directories,
                    pic: true)
