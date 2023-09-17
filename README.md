# ML-based-Feedback-on-FPGA
Use FPGA-based machine learning inference in feedback control to stabilize laser beam and to cancel high frequency noises. This is work to apply machine learning to solve a typical engineering feedback control problem.

# 1. Problem: 
Stabilizing a laser light beam is a common challenge. This stabilization of light, whether it's a laser, X-ray, electron beam or any other type of light, presents a typical feedback problem encountered in engineering. It's crucial for X-ray synchronization experiments, biomedical imaging, and nanofabrication processes in extreme ultraviolet (EUV), deep ultraviolet (DUV), and electron beam lithography. For many cases, traditional feedback theories like Proportional–integral–derivative (PID) controller feedback have successfully addressed this problem.

However, in the case of nonlinear problems, there is no widely accepted standard feedback approach. This work aims to leverage machine learning for feedback control to tackle nonlinear behaviors.

# 2. Optical System and Control Hardware
Figure 1 depicts the structure of the optical system. It comprises two position sensors, each providing horizontal and vertical position data. Additionally, there are two actuators (piezo mirrors), each capable of control in both horizontal and vertical directions. 
Figure 2 illustrates the FPGA-based control system, which includes a Xilinx Zynq-7000 FPGA System on Module (SOM), high-speed ADC, and DAC. The interface between the optical system and the control system relies on analog signals: sensor data is transmitted to the control system as voltages, which are subsequently converted into digital data through the analog-to-digital (ADC) chip integrated into the control system. The control system performs feedback calculations and transmits the output data to the digital-to-analog (DAC) converter chips, which in turn generate voltages for the optical system.
Notably, in this system, we intentionally utilize the actuators as a noise source to simulate environmental vibrations. These actuators are linked to a DAC on the control system, where they receive random data.

![image](https://github.com/kathtian/ML-based-Feedback-on-FPGA/assets/88470317/6edb203e-f3a2-4e1a-8dfe-31048e2477c5)
: Figure 1. Optical system :

![image](https://github.com/kathtian/ML-based-Feedback-on-FPGA/assets/88470317/0063b5b3-6acd-48b6-a1c9-96b08813f1b9)
Figure 2. FPGA-based control system

# 3. Feedback System Architecture
1) Control System: FPGA IO
The control system employs an ADC to read the position sensors and a DAC to govern the piezo mirror. Both the ADC and the DAC utilize the Serial Peripheral Interface (SPI) for digital data communication. A Verilog FPGA Intellectual Property (IP) has been developed to facilitate communication with the ADC and DAC. The FPGA block diagram in Vivado is illustrated in Figure 3.

![image](https://github.com/kathtian/ML-based-Feedback-on-FPGA/assets/88470317/efa517f0-618c-4c79-be6d-46891cbf35f0)
Figure 3. FPGA block diagram in Vivado

2) Control System: EPICS
As depicted in Figure 3, the FPGA sends/receives data from the ADC/DAC as registers in the AXI bus. The ARM processor communicates with the external world (a Linux PC) through TCP/IP sockets. To establish a software control system, a software framework is essential on the PC side. While LabView is one viable option, it's worth noting that many large national labs, dealing with millions of parameters in particle accelerators, require high reliability. Therefore, they often turn to EPICS (Experimental Physics and Industrial Control System), an open-source control system framework. EPICS has been extensively utilized in numerous large national labs for controlling large particle accelerators, demonstrating its reliability and scalability.
The EPICS framework encompasses Ethernet-based protocols, low-level device drivers, and a database designed to manage a substantial quantity of physical parameters. Additionally, it provides an open-source user interface. The framework itself is developed primarily in C/C++, with interfaces available for other programming languages such as Python, Java, Matlab, and LabView. Figure 4 showcases the EPICS system and its user interface, known as Control System Studio.

![image](https://github.com/kathtian/ML-based-Feedback-on-FPGA/assets/88470317/03c08563-85bb-4df4-882a-e580f8ef6093)
Figure 4. EPICS control framework and user interface

# 4. Model-based training 
1) Data Collection
Using the data available from the EPICS control system, which includes control setpoints and position readbacks, we can easily amass a large quantity of data to build a machine learning module. We generated one million setpoints to drive the mirror, and for each setpoint, we collected the corresponding mirror position readbacks. These setpoints and readbacks were sampled at a rate of 10Hz, resulting in 10 data sets per second. Therefore, it took approximately 30 hours to collect the entire one million data sets. The data collection process was implemented in Python, utilizing a Python API called Cothread to interface with the EPICS framework. For data analysis and plotting, we employed Pandas and Matplotlib.

2) Data Training
During the model training phase, we utilized a model-based approach known as dynamic model learning.
The fundamental linear relationship between the sensors and actuators was obtained through system transfer function measurements. However, the basic model had three limitations:
•	The accuracy of the model measurement was highly dependent on the quantity of measurements taken.
•	The model did not account for the nonlinear dynamics of the system, which could be significant in certain ranges of the position sensor and actuator mirror.
•	There was no provision for online reinforcement learning, a critical consideration when the system's behavior can change due to environmental factors, load variations, aging machine components, etc.
Figure 5 illustrates a comprehensive training algorithm, where Sn represents sensor data, An represents actuator data, and "trajectory" denotes the laser positions in both horizontal and vertical directions.
The module was trained using the one million data points on a GPU server equipped with four NVIDIA GPUs running Ubuntu. We utilized TensorFlow, PyTorch, and CUDA for the training process, which took approximately 20 hours to complete.

![image](https://github.com/kathtian/ML-based-Feedback-on-FPGA/assets/88470317/15fd5121-723f-4a71-894d-5450b75d52e3)
Figure 5. Model-based policy optimization training procedure

# 5. ML-Based Feedback Control
1) Inference
Once the deep learning machine module is trained, the inference procedure deploys the module in the feedback control process with the objective of stabilizing laser beam positions. In this context, inference involves reading the current position data, applying the trained machine learning module, and calculating new mirror control data to stabilize the mirror position. From a feedback perspective, this approach is akin to traditional PID feedback control, but instead of employing PID calculations, it utilizes the trained machine learning module.
There are two approaches for inference, depending on where the calculations are executed:
1.	Inference on CPU: In contrast to the complex training process in deep learning, inference calculations are relatively straightforward. These calculations are performed using a Python script running on a laptop, eliminating the need for GPUs. The feedback operates at a rate of 10Hz, including data retrieval from EPICS, inference calculations, and data output to EPICS. While this approach is effective at removing slow or DC noises from the feedback loop, it cannot handle fast noises such as mechanical noise (100Hz~200Hz) or AC line noise (~60Hz). The primary advantage of this approach is its simplicity, as it can be easily deployed with a basic Python script, requiring no special hardware.
2.	On FPGA: MLP-Based: To mitigate high-frequency noises caused by mechanical or floor motion, FPGA-based inference is employed for feedback calculations.
In deep learning, FPGA represents a valuable hardware alternative to GPUs. Numerous research and development efforts have explored FPGA utilization in both training and inference steps. The advantages of FPGA in machine learning include:
•	Real-time Input/Output (IO) Interface: FPGA devices can achieve bit-level IO communication with the physical world, including interfaces like Ethernet, high-speed fiber communication protocols, ADC, DAC, and simple chip-to-chip communication such as SPI/I2C. This enables data collection (input) and data communication during inference (output) at sub-microsecond speeds. In contrast, typical GPU-based training/inference often involves an operating system and software in the loop, making real-time IO challenging.
•	Flexibility: FPGA can be programmed to interface flexibly with the physical world, making it applicable to various scenarios.
•	Deterministic: FPGA calculations, such as convolutional neural networks, occur in deterministic clock cycles, ensuring a deterministic approach in both training and inference steps. In GPU-based ML systems, determinism cannot always be guaranteed, which is critical in certain ML applications like defense systems, low-latency trading, autonomous driving, or fast feedback systems, as in this case.
•	Low Power: FPGA-based systems generally consume less power compared to GPU-based systems.
•	Parallel Processing: FPGA, like GPUs, boasts a large number of calculation units (digital signal processors) that operate in parallel, particularly useful for matrix calculations and tensor operations, compared to CPU-based sequential calculations.
However, one significant obstacle to FPGA application in ML is the lack of tools for easier deployment of training modules on FPGAs. Unlike GPUs, which have a wealth of ML tools like CUDA developed by NVIDIA, FPGA-based systems lack such resources. Bridging the complexity gap between software programming in Python or C and hardware programming in Verilog is a challenge. Various research projects, including OpenCL on FPGA, FASTCUDA, and PYNQ, aim to address this gap and streamline FPGA-based ML deployments.
For our specific case, as described earlier, the DL module training is conducted on a GPU-based server. Fast feedback deployment, i.e., the inference step, is performed on FPGA chips. Figure 6 illustrates the inference steps, essentially a 5-layer multi-layer-perceptron (MLP). FPGA computation can complete these calculations in just a few microseconds. More importantly, as high-speed feedback is employed (at 10KHz), FPGA deployment offers the benefit of achieving real-time feedback: the FPGA directly reads ADC data (position), performs ML inference calculations in parallel on its DSP block, and sends the results to drive the DAC (mirror control) directly. All these feedback operations are completed in less than 10 microseconds, effectively closing the feedback loop at 10 KHz, thereby removing high-frequency noises (up to 1 KHz) from the feedback loop.

![image](https://github.com/kathtian/ML-based-Feedback-on-FPGA/assets/88470317/f7c40bd6-f066-4fb5-b126-a4708309a3af)
Figure 6. MLP inference implementation diagram

The FPGA-based inference block diagram is presented in Figure 3, where ADC, DAC interface, and DSP represent the IP for ML-based inference MLP. The detailed deployment of the MLP is accomplished using Xilinx's Vivado HLS and Vitis. The Vivado high-level synthesis tools are utilized to parse the MLP calculation, incorporating activation functions such as Rectified Linear Unit (ReLU), Sigmoid Function, Tangent Activation Function, and Leaky ReLU. These are tested on FPGA-based inference as well.
Figure 5 outlines the inference calculation procedure, with the HLS code included in this repository.

# 6. Test and Results
After several iterations to optimize our DL module training, primarily following the policy outlined in Figure 5, we achieved a robust module. We used Python-based inference for initial testing, assessing the module's impact, long-term reliability over several days, and its response to corner cases. Once validated in Python, we transitioned to FPGA-based inference design. This entailed adjusting the HLS design, recompiling the FPGA, and programming the flash memory on the FPGA system for the boot-up image. Subsequently, we switched to FPGA-based control for feedback.

![image](https://github.com/kathtian/ML-based-Feedback-on-FPGA/assets/88470317/3ddfc9b9-0e3d-433f-8bb6-3ec258481950)
Figure 7. Noises was removed when ML-based feedback system is on

To compare Python-based inference and FPGA-based inference, we collected position data at a rate of 10 KHz and calculated the power spectrum density (PSD) to assess noise suppression in the two approaches. We concluded that feedback using FPGA-based inference can effectively suppress noises up to 1 KHz, whereas Python-based inference only managed to suppress noise in the 1-5Hz range.




