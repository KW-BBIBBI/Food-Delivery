# WeGo Scout mini Exercise
---
## 💻 팀원
<table>
    <tr height="150px">
        <td align="center" width="130px">
            <a href="https://github.com/syw2045"><img height="100px" width="100px" src="https://avatars.githubusercontent.com/u/81313733?v=4"></a>
            <br/>
            <a href="https://github.com/syw2045">SSong</a>
        </td>
        <td align="center" width="130px">
            <a href="[https://github.com/SaltnLight-pet"><img height="100px" width="100px" src="https://avatars.githubusercontent.com/u/142612336?v=4"></a>
            <br/>
            <a href="https://github.com/SaltnLight-pet">SaltnLight-pet</a>
        <td align="center" width="130px">
            <a href="https://github.com/Heesun0-0"><img height="100px" width="100px" src="https://avatars.githubusercontent.com/u/125299969?v=4"/></a>
            <br/>
            <a href="https://github.com/Heesun0-0">Heesun0-0</a>
        <td align="center" width="130px">
            <a href="https://github.com/JunseoMin"><img height="100px" width="100px" src="https://avatars.githubusercontent.com/u/114414158?v=4"/></a>
            <br/>
            <a href="https://github.com/hongjungin">JunseoMin</a>
        </td>
    </tr>
</table>

--- 

## Enviroment

|OS|Version|
|:---:|:---:|
|Ubuntu|20.04.6 LTS|
|ROS|Noetic|


|HW|Version|
|:---:|:---:|
|ROBOT|WeGo-ST MINI|


## SLAM
### ROBOT
```bash
rosrun scout_bringup bringup_can2usb.bash
roslaunch kw robot_bringup.launch
roslaunch gmapping slam_gmapping_pr2.launch
```
### LOCAL
```bash
roslaunch kw gmapping_display.launch
```
![SLAM](https://github.com/KW-BBIBBI/Food-Delivery/assets/81313733/500b42f8-92b0-400b-b0bc-ee13bc765c50)


## Navigation
### ROBOT
```bash
rosrun scout_bringup bringup_can2usb.bash
roslaunch kw robot_bringup.launch
roslaunch kw navigation.launch
rosrun kw application.py
```
### LOCAL
```bash
roslaunch kw navigation_display.launch
```

![NAVI](https://github.com/KW-BBIBBI/Food-Delivery/assets/81313733/f256cf20-8b09-485f-92d6-59bc07a8c44a)

## Multiwaypoint
![WAYPOINT](https://github.com/KW-BBIBBI/Food-Delivery/assets/125299969/0978ba11-3dcf-4232-9b1d-62c020fd68d2)