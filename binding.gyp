{
  "targets": [
    {
      "target_name": "mouse-controller",
      "sources": ["main.cpp"],
      "include_dirs": [
        "./node_modules/node-addon-api/",
        "<!(node -p \"require('node-addon-api').include\")",
        "<!@(node -p \"require('node-addon-api').include\")",
        "."
      ],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions"],
      "msvs_settings": {
        "VCCLCompilerTool": { "ExceptionHandling": 1 }
      },
      "conditions": [
        ["OS=='mac'", {
          "xcode_settings": {
            "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
          }
        }],
        ["OS=='win'", {
          "msvs_settings": {
            "VCCLCompilerTool": {
              "ExceptionHandling": 1
            }
          }
        }]
      ]
    }
  ]
}