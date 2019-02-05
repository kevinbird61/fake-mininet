# Supported command list

## Main instructions

| Name | Function | Alias |
| :--- | :--- | :--- |
| `create host <name>` | create a virtual host. | `c h <name>` |
| `create switch <name>` | create a virtual switch. | `c sw <name>` |
| `link <name #1> <name #2>` | create a virtual link between 2 points. | |
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
| `debug` | show the current status of network manager. | |