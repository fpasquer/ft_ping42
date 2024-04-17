#!/bin/bash

docker build \
	-t docker_ft_ping \
	--target base \
	./docker/.

docker run \
	-it \
	--rm \
	-v ${PWD}:/app/ft_ping \
	--name ft_ping_container \
	docker_ft_ping \
	bash