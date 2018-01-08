{
  "targets": [
    {
      'target_name': 'pipe_stream',
      'sources': [
        'pipe-stream.cc',
        # headers in case this is used to generate IDE projects
        'pipe-stream.h',
        '../napi-helpers.h'
      ],
      'include_dirs': [
        './', '../'
      ]
    }
  ]
}
