# Web Server in C

![cli_demo](Server/demo/demo.gif)

# **Description**

This program manages Uber-Movement trips information, specifically, it provides a CLI tool to query the average time of a trip based on certain basic trip criteria, namely the ID of the origin location, ID of the destination location and hour of the day.

## **Usage**
First to the Server folder: 
1. Process data.
```bash
make data
```
2. Launch server. 
```bash
make run_server
```

2. Launch client. 
```bash
make run_client
```