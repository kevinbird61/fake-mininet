# Supported command list

## Main instructions

| Name | Function | Alias |
| :--- | :--- | :--- |
| `create host <name>` | create a virtual host. | `c h <name>` |
| `create switch <name>` | create a virtual switch. | `c sw <name>` |
| `link <name #1> <name #2> [up\|down]` | connect/disconnect a virtual link between 2 points. | `l <name #1> <name #2> [up\|down]` |
| `setlink <name #1> <name #2> [cap\|val] <value>` | set the capacity/flow value of the link between 2 specified vertices. | `sl <#1> <#2> [c\|v] <value>` |
| `<name #1> ping <name #2>` | if link is set, then ping will success | |
| `net` | display links | |
| `nodes` | display nodes (switch, host) | |
| `plot` | show the current content of topology. (in dotfile format) | |
| `export [filename]` | export the dotfile. (If you don't specify the filename, then will generate the dotfile with default setting) | |


## Other

| Name | Function | Alias |
| :--- | :--- | ---: |
| `help` | print the helper message. | |
| `exit` | close this fake CLI elegantly. | |
| `clear` | clear and reset the network status (like `mn -c`). | |
| `debug` | show the current status of network manager. | |
