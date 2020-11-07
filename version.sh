#!/bin/sh
set -e

if git describe > /dev/null 2>&1; then
	git describe | tr -d 'v\n'
else
	commit=$(git rev-parse --short HEAD)
	printf "git-%s" "$commit"
fi
