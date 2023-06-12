

platform_sources = [
    'include/platform/configuration.h',
    'include/platform/filesystem.h',
    'include/platform/serialization.h',
    'include/platform/serialization_instantiations.inl',
    'include/platform.h',
    'src/configuration.cpp'
]
platform_include_directories = include_directories('include')

platform_boost_modules = [
    'dll',
    'url',
]
platform_boost_dep = dependency('boost', required: true,
                                modules: platform_boost_modules)

platform_deps = [
    platform_boost_dep,
    cereal_dep
]


platform_lib = library('roughpy_platform', platform_sources,
                       include_directories: platform_include_directories,
                       dependencies: platform_deps,
                       link_with: [core_lib],
                       pic: true)
