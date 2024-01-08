
import re
import sys
import argparse
from logging import Logger, basicConfig, getLogger
from os import getenv, environ
from pathlib import Path
from typing import List

logger = getLogger(__name__)  # type: Logger

include = re.compile('#include\s*["<](.*)[">]\s*')
lib_include = re.compile('#include\s*["<](library/.*)[">]\s*')

lib_include_guard = re.compile('#.*AJAY_.*')

defined = set()

def dfs(f: str) -> List[str]:
    print(f'expanding : {f}')
    global defined
    if f in defined:
        logger.info('already included {}, skip'.format(f))
        return []
    defined.add(f)

    logger.info('include {}'.format(f))
    s = open(str(lib_path / f)).read()

    result = []
    for line in s.splitlines():
        if lib_include_guard.match(line):
            continue
       
        lib_matcher = lib_include.match(line)
        if "library/debug/pprint.hpp" in line:
            lib_matcher = False
        
        if lib_matcher:
            result.extend(dfs(lib_matcher.group(1)))
            continue
        if not lib_matcher:
            std_matcher = include.match(line)
            if std_matcher:
                std_lib = std_matcher.group(1)
                if std_lib in defined:
                    logger.info(f'already included {std_lib}, skip')
                    continue
                defined.add(std_lib)
        result.append(line)
    return result


if __name__ == "__main__":
    basicConfig(
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%H:%M:%S",
        level=getenv('LOG_LEVEL', 'INFO'),
    )
    parser = argparse.ArgumentParser(description='Expander')
    parser.add_argument('source', help='Source File')
    parser.add_argument('--lib', help='Path to Your Library')
    parser.add_argument('--out', help='Output File')
    opts = parser.parse_args()

    lib_path = Path(opts.lib)

    s = open(opts.source).read()

    result = []
    for line in s.splitlines():
        lib_matcher = lib_include.match(line)
      
        if lib_matcher:
            result.extend(dfs(lib_matcher.group(1)))
            continue
        result.append(line)

    output = ""
    for i, line in enumerate(result):
        if i and not result[i - 1] and not result[i]:
            continue
        output += f'{line}\n'
    output += '\n'

    with open(opts.out, 'w') as f:
        f.write(output)