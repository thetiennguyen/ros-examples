# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Overview

This directory (`publisher/`) is a ROS 1 (Catkin) C++ package inside the `ros-examples` repository. It implements a basic ROS publisher node (`talker`) that publishes `std_msgs::String` messages to the `chatter` topic at 10 Hz.

## Build and Run Commands

This package must be built from the root of a Catkin workspace (where `ros-examples` is placed inside `<catkin_ws>/src/`):

```bash
# Source ROS environment (e.g., Kinetic / Noetic)
source /opt/ros/<distro>/setup.bash

# Build all packages or only the publisher package from the workspace root
cd ~/ros_workspace
catkin_make
# Or build strictly this package:
catkin_make --pkg publisher

# Source the workspace overlay
source devel/setup.bash
```

### Running the Node

A `roscore` instance must be running in a separate terminal before starting the node:

```bash
# Terminal 1
roscore

# Terminal 2: Run the publisher executable
# Note: CMakeLists.txt renames the target output from publisher_node to "node"
rosrun publisher node
```

### Running Tests

Tests are configured via Catkin/GTest in `CMakeLists.txt` (currently commented out):

```bash
cd ~/ros_workspace
catkin_make run_tests_publisher
```

## Architecture & Build Configuration

- **`package.xml`**: Declares Catkin format 2 metadata and depends on `roscpp` and `std_msgs`.
- **`CMakeLists.txt`**: Compiles `src/publisher_node.cpp` into the CMake target `publisher_node`, then uses `set_target_properties(... OUTPUT_NAME node PREFIX "")` so the resulting binary is named `node` (invoked via `rosrun publisher node` rather than `rosrun publisher publisher_node`).
- **`src/publisher_node.cpp`**: Initializes the ROS node named `"talker"`, advertises `std_msgs::String` on topic `"chatter"` with a queue size of 1000, and loops at 10 Hz (`ros::Rate(10)`).

## Sibling Packages in `ros-examples`

This package is part of a multi-package ROS 1 example repository containing:
- `publisher` / `subscriber`: Basic `std_msgs::String` pub/sub on topic `chatter`.
- `service` / `client` / `example_srvs`: Service server and client using custom service `example_srvs/AddTwoInts.srv`.
- `example_msgs`: Custom message definitions (`Example.msg`).
- `vision`: OpenCV + ROS integration example.

## Compact Instructions

When compacting the conversation, always preserve:
- List of modified C++ files, CMakeLists.txt changes, and ROS nodes/topics/services affected.
- Current git branch and any uncommitted changes.