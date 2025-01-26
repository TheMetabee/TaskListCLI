# TaskListCLI

This was made to practice my C++ a bit making a simple task tracker task. The task requirements was given at https://roadmap.sh/projects/task-tracker. Only used the standard library.

Example commands:
# Adding a new task
```task-cli.exe add "Buy groceries"```

# Updating and deleting tasks
```task-cli.exe update 1 "Buy groceries and cook dinner"```

```task-cli.exe delete 1```

# Marking a task as in progress or done
```task-cli.exe mark-in-progress 1```

```task-cli.exe mark-done 1```

# Listing all tasks
```task-cli.exe list```

# Listing tasks by status
```task-cli.exe list done```

```task-cli.exe list todo```

```task-cli.exe list in-progress```

# Clear task list
```task-cli.exe clear```

# Building
This was built using VS 2022 with C++ 14. It's only 14 cause I used a lambda but that could easily be replaced with a C++ 11 version if I felt like it. 
