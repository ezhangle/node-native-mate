{
  'targets': [
    {
      'target_name': 'native_mate',
      'type': 'static_library',
      'direct_dependent_settings': {
        'include_dirs': [
          '.',
          'header_redirect',
          'vendor',
        ],
      },
      'export_dependent_settings': [ 'vendor/base-minimal/base.gyp:base', ],
      'dependencies': [ 'vendor/base-minimal/base.gyp:base', ],
      'include_dirs': [
        '.',
        'header_redirect',
      ],
      'sources': [
        'gin/arguments.cc',
        'gin/arguments.h',
        'gin/converter.cc',
        'gin/converter.h',
        'gin/dictionary.cc',
        'gin/dictionary.h',
        'gin/function_template.cc',
        'gin/function_template.h',
        'gin/gin_export.h',
        'gin/handle.h',
        'gin/object_template_builder.cc',
        'gin/object_template_builder.h',
        'gin/try_catch.cc',
        'gin/try_catch.h',
        'gin/wrappable.cc',
        'gin/wrappable.h',
        'header_redirect/uv/include/uv.h',
        'header_redirect/v8/include/v8.h',
        'native_mate/empty.cc',
        'vendor/nan/nan.h',
      ],
    },
  ],
}
