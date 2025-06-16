# IOD
Input on Demand

Might add bindGroups, only issue is that this will trigger lots of pressed and down events?
maybe I can store bind groups seperately and then look at the top most tree and see if it can make a bindgroup and if it can 
add some sort of debounce.

profile.bindGroup({IOD_KEY_SHIFT, IOD_KEY_A}, 
    []() {
        ...
    }
)