from KratosMultiphysics import Model, Parameters

from KratosMultiphysics.FluidDynamicsApplication.fluid_dynamics_analysis import FluidDynamicsAnalysis
from KratosMultiphysics.ConvectionDiffusionApplication.convection_diffusion_analysis import ConvectionDiffusionAnalysis


class DEMCoupledFluidAnalysis(ConvectionDiffusionAnalysis):

    def __init__(self, model, parameters=None, variables_management=None):
        self.model = model
        self.sdem_project_parameters = parameters
        self.fluid_parameters = parameters['fluid_parameters']
        self.vars_man = variables_management

        super().__init__(model, self.fluid_parameters)

        #self.fluid_model_part = self._GetSolver().main_model_part
        
        self.fluid_model_part = 
        self.thermal_model_part = 


    def Initialize(self):
        self.AddFluidVariablesForPlasmaDynamics()
        super().Initialize()


    def AddFluidVariablesForPlasmaDynamics(self):
        self.vars_man.AddNodalVariables(self.fluid_model_part, self.vars_man.fluid_vars)


    def _CreateSolver(self):
        if (self.fluid_parameters["solver_settings"]["solver_type"].GetString() == "MonolithicDEM"):
            from KratosMultiphysics.SwimmingDEMApplication.python_solvers_wrapper_fluidDEM import CreateSolver
            return CreateSolver(self.model, self.fluid_parameters)
        else:
            from KratosMultiphysics.ConvectionDiffusionApplication.python_solvers_wrapper_convection_diffusion import CreateSolver
            return CreateSolver(self.model, self.fluid_parameters)




if __name__ == '__main__':
    from sys import argv

    if len(argv) > 2:
        err_msg =  'Too many input arguments!\n'
        err_msg += 'Use this script in the following way:\n'
        err_msg += '- With default parameter file (assumed to be called "ProjectParameters.json"):\n'
        err_msg += '    "python fluid_dynamics_analysis.py"\n'
        err_msg += '- With custom parameter file:\n'
        err_msg += '    "python fluid_dynamics_analysis.py <my-parameter-file>.json"\n'
        raise Exception(err_msg)

    if len(argv) == 2: # ProjectParameters is being passed from outside
        parameter_file_name = argv[1]
    else: # using default name
        parameter_file_name = "ProjectParameters.json"

    with open(parameter_file_name,'r') as parameter_file:
        parameters = Parameters(parameter_file.read())

    model = Model()
    simulation = DEMCoupledFluidAnalysis(model, parameters)
    simulation.Run()