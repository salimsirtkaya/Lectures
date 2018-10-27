The project is implemented in MatLab, using KiKS (Khepera simulator software). The source codes for KiKS are also included under the directory \\Group5\Source. These files are necessary for proper operation of fastSLAM codes.

The source codes of fastSLAM implementation are under the \\Group5\Source\AI_EE586_fastslam.

In order to run the fastSLAM algortihms (only at first run) you should setup KiKS, by typing "kiks_setup" on MatLab command window under directory \\Group5\Source. Then, follow the instructions to setup KiKS properly. By this way the simulator will adapt itself to your computer, processor speed, memory requirements etc.

Afterwards, you can run fastSLAM in two different modes by typing "FASTSLAM" or "FASTSLAM_lookup" under directory \\Group5\Source\AI_EE586_fastslam. The fastSLAM implementations depend on KiKS. Therefore when you run fastSLAM initially KiKS simulator will automatically start. You should accept the terms and conditions to proceed further. The fastSLAM algorithm will start after that. The output of the algorithm will be a Khepera simulation on the KiKS arena window and the corresponding map and pose estimates, shown simultaneously, on another figure. At the end of the algorithm a summary of the map and pose estimates will be displayed on another figure.

The map is generated within the m-files "FASTSLAM" and "FASTSLAM_lookup". The corresponding motion tracks are generated within the m-files "Kinematics" and "Kinematics_lookup". If you want to change the map you should change the necessary lines in the m-files "FASTSLAM" and "FASTSLAM_lookup" and also change the motion tracks accordingly. Necessary explanations are included in the m-files.

To run the fastSLAM algorithm with synthetic data goto \\Group5\Source\AI_EE586_fastslam\synthetic, and type FASTSLAM_synthetic on the commandline of MatLab. This code does not require KiKS to run. The results are displayed on figures similar to previous case.