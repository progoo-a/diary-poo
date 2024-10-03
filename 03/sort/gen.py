#!/usr/bin/env python
import click 
import numpy as np

@click.command()
@click.option('-n', type=int, help='Elements to generate')
def generate(n):
    elements = np.random.rand(n) * 100
    print(' '.join(map(str, elements)))

if __name__ == '__main__':
    generate()