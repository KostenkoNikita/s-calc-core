{
  "targets": [
    {
      "target_name": "tokenizerModule",
      "sources": [
        "./core/napi-bridge.c",
        "./core/string_list.c",
        "./core/tokenizer.c"
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