@Library('conservify') _

conservifyProperties()

timestamps {
    node () {
        conservifyBuild(name: 'sonar')
        distributeFirmware()
    }

    refreshDistribution()
}
