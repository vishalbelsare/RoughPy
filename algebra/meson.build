


algebra_include_directories = include_directories('include')

algebra_boost_modules = [
    'container',
    'smart_ptr',
    'functional',
]
algebra_boost_dep = dependency('boost', required: true,
                               modules: algebra_boost_modules)


algebra_deps = [
    algebra_boost_dep,
    libalgebra_lite_dep,
]


algebra_soures = [
    'include/roughpy/algebra/algebra_base.h',
    'include/roughpy/algebra/algebra_bundle.h',
    'include/roughpy/algebra/algebra_bundle_impl.h',
    'include/roughpy/algebra/algebra_fwd.h',
    'include/roughpy/algebra/algebra_impl.h',
    'include/roughpy/algebra/algebra_info.h',
    'include/roughpy/algebra/algebra_iterator.h',
    'include/roughpy/algebra/algebra_iterator_impl.h',
    'include/roughpy/algebra/basis.h',
    'include/roughpy/algebra/basis_impl.h',
    'include/roughpy/algebra/basis_info.h',
    'include/roughpy/algebra/bundle_info.h',
    'include/roughpy/algebra/context.h',
    'include/roughpy/algebra/context_fwd.h',
    'include/roughpy/algebra/fallback_operations.h',
    'include/roughpy/algebra/free_tensor.h',
    'include/roughpy/algebra/free_tensor_impl.h',
    'include/roughpy/algebra/lie.h',
    'include/roughpy/algebra/lie_basis.h',
    'include/roughpy/algebra/linear_operator.h',
    'include/roughpy/algebra/shuffle_tensor.h',
    'include/roughpy/algebra/tensor_basis.h',
    'src/libalgebra_lite_internal/dense_vector_iterator.h',
    'src/libalgebra_lite_internal/free_tensor_info.h',
    'src/libalgebra_lite_internal/lie_basis_info.h',
    'src/libalgebra_lite_internal/lie_info.h',
    'src/libalgebra_lite_internal/lite_vector_selector.h',
    'src/libalgebra_lite_internal/sparse_mutable_ref_scalar_trait.h',
    'src/libalgebra_lite_internal/sparse_vector_iterator.h',
    'src/libalgebra_lite_internal/tensor_basis_info.h',
    'src/libalgebra_lite_internal/vector_type_helper.h',
    'src/algebra_base.cpp',
    'src/algebra_iterator.cpp',
    'src/basis.cpp',
    'src/context.cpp',
    'src/double_lite_context.cpp',
    'src/float_lite_context.cpp',
    'src/free_tensor.cpp',
    'src/hall_set_size.cpp',
    'src/hall_set_size.h',
    'src/lie.cpp',
    'src/lie_basis.cpp',
    'src/lite_context.cpp',
    'src/lie_context.h',
    'src/rational_lite_context.cpp',
    'src/shuffle_tensor.cpp',
    'src/tensor_basis.cpp',
]



algebra_lib = library('roughpy_algebra', algebra_sources,
                      include_directories: algebra_include_directories,
                      dependencies: algebra_deps,
                      link_with: [core_lib, platform_lib, scalars_lib],
                      pic: true)


algebra_tests = executable('roughpy_algebra_tests',
                           'src/test_lie.cpp',
                           install: false)
test('algebra_tests', algebra_tests)
