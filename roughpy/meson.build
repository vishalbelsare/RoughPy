
roughpy_module_inc_dir = include_directories('src')

roughpy_module_deps = [
    python_dep,
    pybind_dep
]

roughpy_module_link = [
    core_lib,
    platform_lib,
    scalars_lib,
    intervals_lib,
    algebra_lib,
    streams_lib
]

roughpy_module_sources = [
    'src/algebra/algebra.cpp',
    'src/algebra/algebra.h',
    'src/algebra/algebra_iterator.cpp',
    'src/algebra/algebra_iterator.h',
    'src/algebra/basis.cpp',
    'src/algebra/basis.h',
    'src/algebra/context.cpp',
    'src/algebra/context.h',
    'src/algebra/free_tensor.cpp',
    'src/algebra/free_tensor.h',
    'src/algebra/lie.cpp',
    'src/algebra/lie.h',
    'src/algebra/lie_key.cpp',
    'src/algebra/lie_key.h',
    'src/algebra/lie_key_iterator.cpp',
    'src/algebra/lie_key_iterator.h',
    'src/algebra/lie_letter.cpp',
    'src/algebra/lie_letter.h',
    'src/algebra/setup_algebra_type.h',
    'src/algebra/shuffle_tensor.cpp',
    'src/algebra/shuffle_tensor.h',
    'src/algebra/tensor_key.cpp',
    'src/algebra/tensor_key.h',
    'src/algebra/tensor_key_iterator.cpp',
    'src/algebra/tensor_key_iterator.h',
    'src/args/kwargs_to_path_metadata.cpp',
    'src/args/kwargs_to_path_metadata.h',
    'src/args/kwargs_to_vector_construction.cpp',
    'src/args/kwargs_to_vector_construction.h',
    'src/args/numpy.cpp',
    'src/args/numpy.h',
    'src/intervals/dyadic.cpp',
    'src/intervals/dyadic.h',
    'src/intervals/dyadic_interval.cpp',
    'src/intervals/dyadic_interval.h',
    'src/intervals/interval.cpp',
    'src/intervals/interval.h',
    'src/intervals/intervals.cpp',
    'src/intervals/intervals.h',
    'src/intervals/real_interval.cpp',
    'src/intervals/real_interval.h',
    'src/intervals/segmentation.cpp',
    'src/intervals/segmentation.h',
    'src/scalars/scalar_type.cpp',
    'src/scalars/scalar_type.h',
    'src/scalars/scalar.cpp',
    'src/scalars/scalar.h',
    'src/streams/BaseStream.cpp',
    'src/streams/BaseStream.h',
    'src/streams/brownian_stream.cpp',
    'src/streams/brownian_stream.h',
    'src/streams/externally_sourced_stream.cpp',
    'src/streams/externally_sourced_stream.h',
    'src/streams/function_stream.cpp',
    'src/streams/function_stream.h',
    'src/streams/lie_increment_stream.cpp',
    'src/streams/lie_increment_stream.h',
    'src/streams/piecewise_abelian_stream.cpp',
    'src/streams/pieceiwse_abelian_stream.h',
    'src/streams/schema.cpp',
    'src/streams/schema.h',
    'src/streams/stream.cpp',
    'src/streams/stream.h',
    'src/streams/streams.cpp',
    'src/streams/streams.h',
    'src/streams/tick_stream.cpp',
    'src/streams/tick_stream.h',
    'src/recombine.cpp',
    'src/recombine.h',
    'src/roughpy_module.cpp',
    'src/roughpy_module.h'
]



roughpy_module = python.extension_module('_roughpy', roughpy_module_sources,
                                         include_directories: roughpy_module_inc_dir,
                                         dependencies: roughpy_module_deps,
                                         link_with: roughpy_module_link
                                         )
