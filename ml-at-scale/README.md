# Machine Learning and Foundation Models at Scale

Sam Foreman  
[2024 ALCF Hands-on HPC Workshop](https://www.alcf.anl.gov/events/2024-alcf-hands-hpc-workshop)

- Slides: <https://samforeman.me/talks/alcf-hpc-workshop-2024/slides>
    - HTML version: <https://samforeman.me/talks/alcf-hpc-workshop-2024>

## Hands On

1. Clone repos:

    1. [`saforem2/wordplay`](https://github.com/saforem2/wordplay):

        ```bash
        git clone https://github.com/saforem2/wordplay
        cd wordplay
        ```

    1. [`saforem2/ezpz`](https://github.com/saforem2/ezpz):

        ```bash
        git clone https://github.com/saforem2/ezpz deps/ezpz
        ```

1. Setup python:

    ```bash
    export PBS_O_WORKDIR=$(pwd) && source deps/ezpz/src/ezpz/bin/utils.sh
    ezpz_setup_python
    ezpz_setup_job
    ```

1. Install `{ezpz, wordplay}`:

    ```bash
    python3 -m pip install -e deps/ezpz --require-virtualenv
    python3 -m pip install -e .
    ```

1. On Polaris:

    ```bash
    unset NCCL_COLLNET_ENABLE NCCL_CROSS_NIC NCCL_NET NCCL_NET_GDR_LEVEL
    ```

1. Test Distributed Setup:

    ```bash
    launch python3 -m ezpz.test_dist
    ```

    See: [`ezpz/test_dist.py`](https://github.com/saforem2/ezpz/blob/main/src/ezpz/test_dist.py)

1. Prepare Data:

    ```bash
    python3 data/shakespeare_char/prepare.py
    ```

1. Launch Training:

    ```bash
    launch python3 -m wordplay \
        train.backend=DDP \
        train.eval_interval=100 \
        data=shakespeare \
        train.dtype=bf16 \
        model.batch_size=64 \
        model.block_size=1024 \
        train.max_iters=1000 \
        train.log_interval=10 \
        train.compile=false \
    ```
