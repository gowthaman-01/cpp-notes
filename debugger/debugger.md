# Debugger Stepping Functions

### Step Into  
- Executes the next statement.  
- If the statement contains a function call, **enters the function** and debugs it line by line.   

### Step Over 
- Executes the next statement but **skips over function calls** by running them entirely.  
- Control returns after the function completes.  
- Ideal for skipping functions that don't need debugging.  

### Step Out  
- **Finishes execution** of the current function and returns control to the caller.  
- Useful when you’ve entered a function by mistake and want to exit quickly.  

### Run to cursor 
- Executes the program until execution reaches the statement selected by your mouse cursor.

### Continue / Start
- Runs the program, until the program terminates or a breakpoint is hit. 
- Start is the same as continue, just from the beginning of the program.

### Set next statement 
- Changes the point of execution to some other statement (sometimes informally called jumping). This can be used to jump the point of execution forwards and skip some code that would otherwise execute, or backwards and have something that already executed run again.


