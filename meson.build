

project('RoughPy', 'c', 'cpp',
    default_options: [ 'c_std=c11', 'cpp_std=c++17']
    )


cc = get_compiler('cpp')
cmake = import('cmake')
python = import('python')

gtest_dep = dependency('gtest', main: true, required: false)
pybind_dep = dependency('pybind11')

python_dep = python.dependency()
cereal_dep = cmake.subproject('external/cereal').dependency()
csvparser_dep = cmake.subproject('external/csv-parser').dependency()
dlpack_dep = cmake.subproject('external/dlpack').dependency()
libalgebra_lite_dep = cmake.subproject('external/libalgebra_lite').dependency()
eigen_dep = dependency('eigen', required: true)
sndfile_dep = dependency('sndfile', required: true)

subdir('core')
subdir('platform')
subdir('scalars')
subdir('intervals')
subdir('algebra')
subdir('streams')

if get_option('build_la_contexts').enabled()
    subdir('la_context')
endif

if get_option('build_device_code').enabled()
    subdir('device')
endif

subdir('roughpy')
