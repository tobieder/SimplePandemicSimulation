# Simple Pandemic Simulation

This project is a simple tool to visualize the spreading of a disease through humans. 
There are a range of parameters to control the human behaviour, immunization, the disease itself and the adoption of social distancing.
The realtime data gets displayed numerically as well as using an Area Chart.

This simulation was inspired by a Washington Post [article](https://www.washingtonpost.com/graphics/2020/world/corona-simulator/) published on 14th March 2020.

<p align="center">
  <img width="900" height="507" src="/Resources/sps_showcase.gif">
</p>

## Parameters

### Humans
- Number of humans
- Initial infected humans
- Speed

### Immunization
- Initial number of immune humans

### Disease
- Contagious period
- Contagious variance
- Infection probability

### Social Distancing
- Number of humans that adopt social distancing


## Requirements
The project uses [Qt 5.12.2](www.qt.io).
Additionally the QtCharts and DataVisualization modules are used.
