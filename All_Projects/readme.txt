OPENCV_INCLUDE_DIR : $(SolutionDir)External\opencv43\include
OPENCV_LIBS_NAME : opencv_stitching430d.lib;opencv_superres430d.lib;opencv_xfeatures2d430d.lib;opencv_face430d.lib;opencv_optflow430d.lib;opencv_stereo430d.lib;opencv_xobjdetect430d.lib;opencv_videostab430d.lib;opencv_dpm430d.lib;opencv_tracking430d.lib;opencv_ccalib430d.lib;opencv_ximgproc430d.lib;opencv_bgsegm430d.lib;opencv_rgbd430d.lib;opencv_objdetect430d.lib;opencv_datasets430d.lib;opencv_video430d.lib;opencv_structured_light430d.lib;opencv_shape430d.lib;opencv_rapid430d.lib;opencv_aruco430d.lib;opencv_calib3d430d.lib;opencv_bioinspired430d.lib;opencv_gapi430d.lib;opencv_highgui430d.lib;opencv_line_descriptor430d.lib;opencv_saliency430d.lib;opencv_xphoto430d.lib;opencv_videoio430d.lib;opencv_reg430d.lib;opencv_hfs430d.lib;opencv_img_hash430d.lib;opencv_features2d430d.lib;opencv_imgcodecs430d.lib;opencv_photo430d.lib;opencv_plot430d.lib;opencv_quality430d.lib;opencv_phase_unwrapping430d.lib;opencv_fuzzy430d.lib;opencv_imgproc430d.lib;opencv_surface_matching430d.lib;opencv_flann430d.lib;opencv_ml430d.lib;opencv_intensity_transform430d.lib;opencv_core430d.lib
OPENCV_LIBS_DIR : $(SolutionDir)External\opencv43\x64\vc16\lib
OPENCV_DLLS_DIR : $(SolutionDir)External\opencv43\x64\vc16\bin
OUTPUT_DIR : $(SolutionDir)Output\$(Platform)\Binaries\$(ProjectName)

copy /Y $(OPENCV_DLL_DIR)\opencv_core430d.dll $(SolutionDir)Output\$(Platform)\Binaries\$(ProjectName)
copy /Y $(OPENCV_DLL_DIR)\opencv_videoio430d.dll $(SolutionDir)Output\$(Platform)\Binaries\$(ProjectName)
copy /Y $(OPENCV_DLL_DIR)\opencv_imgproc430d.dll $(SolutionDir)Output\$(Platform)\Binaries\$(ProjectName)
copy /Y $(OPENCV_DLL_DIR)\opencv_imgcodecs430d.dll $(SolutionDir)Output\$(Platform)\Binaries\$(ProjectName)
copy /Y $(OPENCV_DLL_DIR)\opencv_highgui430d.dll $(SolutionDir)Output\$(Platform)\Binaries\$(ProjectName)