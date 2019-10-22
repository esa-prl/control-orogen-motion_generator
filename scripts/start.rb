require 'orocos'
include Orocos

# Initialize orocos ##
Orocos.initialize

## Execute the task 'messages::Producer' ##
Orocos.run 'Task::motion_generator' => 'motion_generator' do
    ## Get the task context##
    motion_generator = Orocos.name_service.get 'motion_generator'

    ## Configure the task
    motion_generator.configure

    ## Start the task ##
    motion_generator.start
end

