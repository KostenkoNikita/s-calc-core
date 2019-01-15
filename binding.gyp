{
  "targets": [
    {
      "target_name": "tokenizerModule",
      "sources": [
        "./core/n-api/napi-bridge.c",
        "./core/common/string_list.c",
        "./core/tokenizer/tokenizer.c"
      ],
      "cflags_cc": [
        "-std=c99",
        "-O3",
        "-ffast-math",
        "-s"
      ]
    }
  ]
}