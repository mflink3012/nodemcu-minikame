# /servos/
Will do actions on the servos.

## Usage
    /servos/?action={action}       For actions on all servos.
    /servos/fll/?action={action}   For actions on the front-left lifting servo.
    /servos/flt/?action={action}   For actions on the front-left turning servo.
    /servos/frl/?action={action}   For actions on the front-right lifting servo.
    /servos/frt/?action={action}   For actions on the front-right turning servo.
    /servos/bll/?action={action}   For actions on the back-left lifting servo.
    /servos/blt/?action={action}   For actions on the back-left turning servo.
    /servos/brl/?action={action}   For actions on the back-right lifting servo.
    /servos/brt/?action={action}   For actions on the back-right turning servo.

## URI-Parameters are:
### `action={action}`

With `{action}` in

`power`

> To enable/disable the servos(s).  
> For `/servos/{resource-id}/`: Dis-/enables only this servo.  
> For `/servos/`: Dis-/enables all servos.  
> The body has to contain a `0` for `disable` or a `1` for `enable`.

`rotate`

> To rotate the servos (simultaneously).  
> For `/servos/{resource-id}/`:

>> The body needs to have 3 digits representing a positive integer defining the angle in degrees the servo has to be rotated absolutely.  
>> If the angle is below 100, it has to be prefixed by zero (e.g. 099, 098, ..., 001, 000).

> For `/servos/`:

>> The body must contain one or more (max. 8) concatenations of `{resource-id}{angle}` per line.  
>> It must contain one or more lines.  
>> `{resource-id}` is one of

>>> `fll` for actions on the front-left lifting servo.  
>>> `flt` for actions on the front-left turning servo.  
>>> `frl` for actions on the front-right lifting servo.  
>>> `frt` for actions on the front-right turning servo.  
>>> `bll` for actions on the back-left lifting servo.  
>>> `blt` for actions on the back-left turning servo.  
>>> `brl` for actions on the back-right lifting servo.  
>>> `brt` for actions on the back-right turning servo.  

>> `{angle}` is a positive integer defining the degrees the servo has to be rotated absolutely. It needs to have 3 digits. If the angle is below 100, it has to be prefixed by zero (e.g. 099, 098, ..., 001, 000).  

>> Example (of one body):

```
            fll090frl120bll010brl030flt000frt045blt045brt090
            fll090frl120blt045brt090
            flt000
```
