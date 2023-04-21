#!/bin/bash
cpplint src/main.cc
cpplint src/renderer.h src/renderer.cc
cpplint src/texture.h src/texture.cc
cpplint src/font.h src/font.cc
cpplint src/frame_rate.h src/frame_rate.cc