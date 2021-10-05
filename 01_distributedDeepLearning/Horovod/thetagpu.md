# Hands on for Data Parallel Deep Learning on ThetaGPU

1. Request an interactive session on ThetaGPU:
```bash
# Login to theta
ssh -CY user@theta.alcf.anl.gov
# prepare dataset
sh prepare_dataset.sh
# Login to ThetaGPU login node
ssh -CY thetagpusn1 
# Requesting 1 node 
qsub -n 1 -q training-gpu -A SDL_Workshop -I -t 2:00:00
```

2. Setup the Python environment to include TensorFlow, Keras, PyTorch, and Horovod:
   ```bash
   . /etc/profile.d/z00_lmod.sh
   module load conda
   conda activate
   ```
   Notice that the first line is needed if you are setting up the environment in a submission script. It is not needed if you are running in interactive mode. 
3. Run examples on a single node
   - PyTorch MNIST - 8 GPUs
     ```bash
     mpirun -np 8 python pytorch_mnist.py --device gpu
     ```

   - PyTorch CIFAR10 - 8 GPUs
     ```bash
     mpirun -np 8 python pytorch_cifar10.py --device gpu
     ```

   -  TensorFlow MNIST - 8 GPUs
      ```bash
      mpirun -np 8 python tensorflow2_mnist.py --device gpu
      ```

   - TensorFlow Keras MNIST - 8 GPUs
     ```bash
     mpirun -np 8 python  tensorflow2_keras_mnist.py --device gpu
     ```
     
4. Test scaling and investigate the issue of large batch size training
The following script performes a simple scaling test with the MNIST dataset and a PyTorch model:
   ```bash
   for n in 1 2 4 8
   do
     	mpirun -np $n python pytorch_mnist.py --device gpu >& pytorch_mnist.out.$n
   done
   ```
   If you want to go to larger scale (16 GPUs), you could run on 2 nodes. 
  ```bash
  mpirun -x LD_LIBRARY_PATH -x PATH -x PYTHONPATH -np 16 -npernode 8 --hostfile $COBALT_NODEFILE  python pytorch_mnist.py --device gpu >& pytorch_mnist.out
  ```
   You can check the test accuracy and the timing for different scales.
  
   We have prepared some (non-interactive) submission scripts in `./submissions/thetagpu/qsub_*`
   
   
   **PyTorch**
   
   Time for 32 epochs 
   
| GPUs | Cifar10 (s) | MNIST (s) |
| ---- | ---------------------- | -------------------- |
|    1 |            522.3       |         499.8        |
|    2 |            318.8       |         283.9        |
|    4 |            121.4       |         100.4        |
|    8 |             73.5       |         58.8         |
|   16 |             79.1       |         63.8         |
|   32 |             81.1       |         55.7         |   
