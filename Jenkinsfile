@Library('conservify') _

conservifyProperties()

timestamps {
    node () {
        conservifyBuild(name: 'sonar', archive: true)
        distributeFirmware()
    }

    refreshDistribution()
}
