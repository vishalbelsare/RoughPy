

scalars_include_directories = include_directories('include')

scalars_boost_modules = [
    'multiprecision',
]

scalars_boost_deps = dependency('boost', required: true,
                                modules: scalars_boost_modules)

scalars_deps = [
    scalars_boost_deps,

]

scalars_sources = [
  'include/roughpy/scalars/key_scalar_array.h',
  'include/roughpy/scalars/owned_scalar_array.h',
  'include/roughpy/scalars/random.h',
  'include/roughpy/scalars/scalar.h',
  'include/roughpy/scalars/scalar_array.h',
  'include/roughpy/scalars/scalar_blas.h',
  'include/roughpy/scalars/scalar_interface.h',
  'include/roughpy/scalars/scalar_matrix.h',
  'include/roughpy/scalars/scalar_pointer.h',
  'include/roughpy/scalars/scalar_stream.h',
  'include/roughpy/scalars/scalar_traits.h',
  'include/roughpy/scalars/scalar_type.h',
  'include/roughpy/scalars/scalars_fwd.h',
  'include/roughpy/scalars.h',
  'src/b_float_16_type.cpp',
  'src/b_float_16_type.h',
  'src/bfloat16_random_generator.cpp',
  'src/bfloat16_random_generator.h',
  'src/double_type.cpp',
  'src/double_type.h',
  'src/float_blas.cpp',
  'src/float_blas.h',
  'src/float_type.cpp',
  'src/float_type.h',
  'src/half_random_generator.cpp',
  'src/half_random_generator.h',
  'src/half_type.cpp',
  'src/half_type.h',
  'src/key_scalar_array.cpp',
  'src/owned_scalar_array.cpp',
  'src/random_impl.cpp',
  'src/random_impl.h',
  'src/rational_poly_scalar_type.cpp',
  'src/rational_poly_scalar_type.h',
  'src/RationalType.cpp',
  'src/RationalType.h',
  'src/scalar.cpp',
  'src/scalar_array.cpp',
  'src/scalar_blas.cpp',
  'src/scalar_blas_impl.h',
  'src/scalar_interface.cpp',
  'src/scalar_matrix.cpp',
  'src/scalar_pointer.cpp',
  'src/scalar_stream.cpp',
  'src/scalar_type.cpp',
  'src/standard_random_generator.cpp',
  'src/standard_random_generator.h',
  'src/standard_scalar_type.h'
]


scalars_lib = library('roughpy_scalars', scalars_sources,
                      include_directories: scalars_include_directories,
                      link_with: [core_lib, platform_lib],
                      dependencies: [scalars_dependencies],
                      pic: true)
