# pangolin-libtorch-issue

_Follow up: https://github.com/stevenlovegrove/Pangolin/issues/884_

Pangolin (https://github.com/stevenlovegrove/Pangolin) is a popular GUI for SLAM system, and libtorch is the C++ library of pytorch, used for deep learning.

The current trend is to apply deep learning to SLAM system, hence it would be great that Pangolin and libtorch work well together. However, the [current version of Pangolin](https://github.com/stevenlovegrove/Pangolin) (commit: June 7, 2023 [d484494](https://github.com/stevenlovegrove/Pangolin/commit/d484494645cb7361374ac0ef6b27e9ee6feffbd7)) and [libtorch 2.0.1](https://download.pytorch.org/libtorch/cu117/libtorch-cxx11-abi-shared-with-deps-2.0.1%2Bcu117.zip) seem to be inconsistent at runtime. After compiling an application with Pangolin and libtorchk, a rare segmentation fault is issued when calling `pangolin::CreateWindowAndBind`. The detailed backtrace is:
```
Pass 'Combine redundant instructions' is not initialized.                                                                                                                                                                                                                 
Verify if there is a pass dependency cycle.                                                                                                                                                                                                                             
Required Passes:                                                                                                                                            

Thread 1 "pangolin_libtor" received signal SIGSEGV, Segmentation fault.                                                                                                                                                                                                   
0x00007f77aa67b378 in llvm::PMTopLevelManager::schedulePass(llvm::Pass*) ()                                                                                                                                                                                             
   from /lib/x86_64-linux-gnu/libLLVM-12.so.1                                                                                                                                                                                                                           
(gdb) bt                                                                                                                    
#0  0x00007f77aa67b378 in llvm::PMTopLevelManager::schedulePass(llvm::Pass*) ()                                                                                                                                                                                         
   from /lib/x86_64-linux-gnu/libLLVM-12.so.1                                                                                                                                                                                                                           
#1  0x00007f77af98a0a7 in ?? () from /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so                                                                                                                                                                                        
#2  0x00007f77af98a190 in ?? () from /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so                                                                                                                                                                                        
#3  0x00007f77afa057b7 in ?? () from /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so                                                                                                                                                                                        
#4  0x00007f77af9f7438 in ?? () from /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so                                                                                                                                                                                        
#5  0x00007f77af9dd9d0 in ?? () from /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so                                                                                                                                                                                        
#6  0x00007f77aff38bfd in ?? () from /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so                                                                                                                                                                                        
#7  0x00007f77aff38f10 in ?? () from /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so                                                                                                                                                                                        
#8  0x00007f77aff394b6 in ?? () from /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so                                                                                                                                                                                        
#9  0x00007f77aff3c13c in ?? () from /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so                                                                                                                                                                                        
#10 0x00007f77aff3cd72 in ?? () from /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so                                                                                                                                                                                        
#11 0x00007f77afa0a837 in ?? () from /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so                                                                                                                                                                                        
#12 0x00007f77af2eab43 in ?? () from /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so                                                                                                                                                                                        
#13 0x00007f77af2e6081 in ?? () from /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so                                                                                                                                                                                        
#14 0x00007f77af2eb02e in ?? () from /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so                                                                                                                                                                                        
#15 0x00007f77af34771a in ?? () from /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so                                                                                                                                                                                        
#16 0x00007f77af347a0a in ?? () from /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so                                                                                                                                                                                        
#17 0x00007f77af2ea981 in ?? () from /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so                                                                                                                                                                                        
#18 0x00007f77af8c8cea in ?? () from /usr/lib/x86_64-linux-gnu/dri/swrast_dri.so                                                                                                                                                                                        
#19 0x00007f77b4871656 in ?? () from /lib/x86_64-linux-gnu/libGLX_mesa.so.0                                                                                                                                                                                             
#20 0x00007f77b48762be in ?? () from /lib/x86_64-linux-gnu/libGLX_mesa.so.0                                                                                                                                                                                             
#21 0x00007f783e9b0e93 in ?? () from /lib/x86_64-linux-gnu/libGLX.so.0                                                                                                                                                                                                  
#22 0x00007f783e9b1467 in ?? () from /lib/x86_64-linux-gnu/libGLX.so.0                                                                                                                                                                                                  
#23 0x00007f783e9b2c58 in ?? () from /lib/x86_64-linux-gnu/libGLX.so.0                                                                                                                                                                                                  
#24 0x00007f7844c80ac1 in pangolin::X11Window::MakeCurrent(__GLXcontextRec*) ()                                                                                                                                                                                         
   from /workspace/install2/lib/libpangolin.so                                                                                                                                                                                                                     
#25 0x00007f7844c80f7d in pangolin::X11Window::MakeCurrent() ()                                                                                                                                                                                                         
   from /workspace/install2/lib/libpangolin.so                                                                                                                                                                                                                     
#26 0x00007f7844bb9ea5 in pangolin::CreateWindowAndBind(std::__cxx11::basic_string<char,                                                                                                                                                                                std::char_traits<char>, std::allocator<char> >, int, int, pangolin::Params const&) ()                                                                                                                                                                                   
   from /workspace/install2/lib/libpangolin.so                                                                                                                                                                                                                     
#27 0x00000000004025a7 in main ()                                                                                                                                                                                               
--Type <RET> for more, q to quit, c to continue without paging--                                                                                                                                                                                                          
    at /workspace/pangolin_libtorch/pangolin_libtorch.cpp:9
```

In this repository, we provide a minimal code to reproduce and debug the problem. There are basically three exectuables:
* `pangolin_libtorch_test`: uses Pangolin and libtorch. It Failed to run and generated the above message.
* `pangolin_alone_test`: use only Pangolin. It runs successfully.
* `opengl_libtorch_test`: use OpenGL and Pangolin. It runs successfully.

I googled the error message, but didn't find anything useful except: https://github.com/horovod/horovod/issues/3415. It seems like there are some symbol conflicts between Pangolin and libtorch, but I am not sure.

I aslo tried to compile Pangolin as a static library, w/o `-fvisibility=hidden` (by modifying Pangolin's CMakeLists.txt). None of them worked.

## System info

* ubuntu 22.04
* libtorch 2.0.1: https://download.pytorch.org/libtorch/cu117/libtorch-cxx11-abi-shared-with-deps-2.0.1%2Bcu117.zip

```
$ glxinfo | grep OpenGL
OpenGL vendor string: Mesa/X.org
OpenGL renderer string: llvmpipe (LLVM 12.0.0, 256 bits)
OpenGL core profile version string: 4.5 (Core Profile) Mesa 21.2.6
OpenGL core profile shading language version string: 4.50
OpenGL core profile context flags: (none)
OpenGL core profile profile mask: core profile
OpenGL core profile extensions:
OpenGL version string: 3.1 Mesa 21.2.6
OpenGL shading language version string: 1.40
OpenGL context flags: (none)
OpenGL extensions:
OpenGL ES profile version string: OpenGL ES 3.2 Mesa 21.2.6
OpenGL ES profile shading language version string: OpenGL ES GLSL ES 3.20
OpenGL ES profile extensions:
```

## Further study

Since the above error is related to GLX, I tried a branch of Pangolin which [replaced GLX by EGL](https://github.com/stevenlovegrove/Pangolin/pull/389).
* __This branch can compile and the example HelloPangolin works well.__
* The example `pangolin_libtorch_test` gives
```
Thread 1 "pangolin_libtor" received signal SIGSEGV, Segmentation fault.
__GI___libc_free (mem=0x1) at malloc.c:3102
3102    malloc.c: No such file or directory.
(gdb) bt
#0  __GI___libc_free (mem=0x1) at malloc.c:3102
#1  0x00007f65aeadee69 in llvm::cl::Option::~Option() () from /workspace/build/_deps/torch-src/lib/libtorch_cpu.so
#2  0x00007f6562f8ffde in __cxa_finalize (d=0x7f65c08ec000) at cxa_finalize.c:83
#3  0x00007f65aa4c9d33 in __do_global_dtors_aux () from /workspace/build/_deps/torch-src/lib/libtorch_cpu.so
#4  0x00007ffec316a970 in ?? ()
#5  0x00007f65c92d3f6b in _dl_fini () at dl-fini.c:138
Backtrace stopped: frame did not save the PC
```
Clearly this error is on Pytorch's side.  Both messages point to LLVM, indicating a symbol conflict.

After googling this message, more information is found:
* Qt + libtorch: https://github.com/pytorch/pytorch/issues/103756
* Valkun + libtorch: https://github.com/pytorch/pytorch/issues/102533
* SDL + libtorch: https://github.com/pytorch/pytorch/issues/71283

Moreover, I find that `opengl_libtorch_test` also generates the same segfault (since the message is different from the previous one, I just ignored it yesterday).

In https://github.com/pytorch/pytorch/issues/103756, a patch is provided just two weeks ago (https://github.com/pytorch/builder/pull/1445). So I tried the nightly built version [`2.1.0.dev20230724+cu118`](https://download.pytorch.org/libtorch/nightly/cu118/libtorch-cxx11-abi-shared-with-deps-latest.zip) (accessed on July 25, 2023), and found that it works for both Pangolin & OpenGL, and all above issues are gone.
