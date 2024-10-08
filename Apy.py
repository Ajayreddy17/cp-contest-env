import os
import sys
from io import BytesIO, IOBase
 
_str = str
str = lambda x = b"": x if type(x) is bytes else _str(x).encode()
 
BUFSIZE = 8192
class FastIO(IOBase):
    newlines = 0
 
    def __init__(self, file):
        self._file = file
        self._fd = file.fileno()
        self.buffer = BytesIO()
        self.writable = "x" in file.mode or "r" not in file.mode
        self.write = self.buffer.write if self.writable else None
 
    def read(self):
        while True:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            if not b:
                break
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines = 0
        return self.buffer.read()
 
    def readline(self):
        while self.newlines == 0:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            self.newlines = b.count(b"\n") + (not b)
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines -= 1
        return self.buffer.readline()
 
    def flush(self):
        if self.writable:
            os.write(self._fd, self.buffer.getvalue())
            self.buffer.truncate(0), self.buffer.seek(0)
 
class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        self.write = lambda s: self.buffer.write(s.encode("ascii"))
        self.read = lambda: self.buffer.read().decode("ascii")
        self.readline = lambda: self.buffer.readline().decode("ascii")
 
sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")
mi = lambda: map(int, input().split())
fi = lambda: map(float, input().split())
si = lambda: input().split()
ii = lambda: int(input())
li = lambda: list(mi())
 
from collections import deque, defaultdict, Counter
from heapq import heapify, heappop, heappush
from itertools import permutations, accumulate
from math import gcd, log, sqrt, floor, ceil
from bisect import bisect_left

MOD = 998244353

import queue

q = deque()

x, y = mi()
dist = [float('inf') for _ in range(20005)]

q.append(x)
dist[x] = 0

lim = 20001

vis = set()

while q:
    cur = q.popleft()
    if cur % 5 == 0:
        if cur // 5 not in vis:
            dist[cur // 5] = 1 + dist[cur]
            q.append(cur // 5)
    if cur % 11 == 0:
        if dist[cur // 11] > 1 + dist[cur]:
            dist[cur // 11] = 1 + dist[cur]
            q.append(cur // 11)
    if cur + 1 < lim:
        if dist[cur + 1] > 1 + dist[cur]:
            dist[cur + 1] = 1 + dist[cur]
            q.append(cur + 1)
    if cur - 1 >= 0:
        if dist[cur - 1] > 1 + dist[cur]:
            dist[cur - 1] = 1 + dist[cur]
            q.append(cur - 1)

print(dist[y])