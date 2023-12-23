# minishell

# Project Environment Variable Management

## Overview

In our project, we adopt a flexible approach to manage environment variables, combining the efficiency of linked lists for dynamic updates and the simplicity of arrays for seamless integration with the `exec` function.

## Key Features

### 1. Linked List Management

We leverage linked lists for handling environment variables within our project. Linked lists provide a convenient structure for efficient insertion and deletion operations. This approach ensures dynamic adaptability, allowing us to easily update the environment variables during runtime.

### 2. Array Representation for `exec` Function

When passing environment variables to the `exec` function, we use an array representation. This enables a straightforward integration with the `exec` function, streamlining the execution process. To maintain synchronization between the linked list and the array, we update the array each time we pass environment variables to `exec`.

## Why This Approach?

Our chosen approach strikes a balance between the ease of managing environment variables through linked lists and the practicality of using arrays for seamless integration with the `exec` function.
