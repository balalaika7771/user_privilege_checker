{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "src/check_privilege.cpp" ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      "libraries": [ "Netapi32.lib" ],
	  "defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS" ]
    }
  ]
}
