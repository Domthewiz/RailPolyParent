# Custom Miyamoto sprites.py Module
# Sprites Images

import math

from PyQt5 import QtCore, QtGui
from PyQt5.QtCore import *
from PyQt5.QtGui import *

Qt = QtCore.Qt

import miyamoto.spritelib as SLib

ImageCache = SLib.ImageCache

# Global varible for rotations.
Rotations = [0, 0, 0]
StoneRotation = 0

class SpriteImage_ControllerSpinning_Shifting(SLib.SpriteImage_MovementController):  # 118
    Speeds = [0x400000, 0x800000, 0xc00000, 0x1000000, 0x200000, 0x2000000, 0x4000000, 0x100000]

    def __init__(self, parent):
        super().__init__(
            parent,
            3.75,
            ImageCache['ControllerSpinning_Shifting'],
        )
        self.aux.append(SLib.AuxiliaryRotationAreaOutline(parent, 60))
        self.aux.append(SLib.AuxiliaryRotationAreaOutline(parent, 120))
        self.xOffset = -8
        self.yOffset = -8
    @staticmethod
    def loadImages():
        SLib.loadIfNotInImageCache('ControllerSpinning_Shifting', 'controller_spinning_shifting.png')

    def dataChanged(self):
        self.rotation = (self.parent.spritedata[2] >> 4) * 22.5
        arc = (self.parent.spritedata[7] >> 4) * 22.5
        self.spinMode = self.parent.spritedata[3] & 3
        reversedDir = self.parent.spritedata[7] & 0xF > 7
        speedValue = self.parent.spritedata[7] & 0xF

        if speedValue > 7:
            speedValue -= 8

        self.rotationSpeed = (SpriteImage_ControllerSpinning_Shifting.Speeds[speedValue] / 0x100000000) * 360

        if reversedDir:
            self.rotation = -self.rotation
            self.rotationSpeed = -self.rotationSpeed

        if self.spinMode == 1:
            arc = 360

        self.aux[0].SetAngle(90 + self.rotation - (arc if reversedDir else 0), arc)
        self.aux[1].SetAngle(90 + self.rotation, 0)
        self.parent.updateScene()
        super().dataChanged()

    def active(self):
        return self.spinMode == 1

    def getStartRotation(self):
        if self.spinMode == 1:
            return -self.rotation - SLib.RotationFrame * self.rotationSpeed * (60 / SLib.RotationFPS)
        else:
            return -self.rotation

class SpriteImage_ControllerSwaying_Shifting(SLib.SpriteImage_MovementController):  # 116
    def __init__(self, parent):
        super().__init__(
            parent,
            3.75,
            ImageCache['ControllerSwaying_Shifting'],
        )

        self.aux.append(SLib.AuxiliaryRotationAreaOutline(parent, 60))
        self.aux.append(SLib.AuxiliaryRotationAreaOutline(parent, 120))

        self.rotation = 0
        self.startOffset = 0
        self.arc = 0
        self.eventActivated = False
        self.xOffset = -8
        self.yOffset = -8

    @staticmethod
    def loadImages():
        SLib.loadIfNotInImageCache('ControllerSwaying_Shifting', 'controller_swaying_shifting.png')

    def dataChanged(self):
        self.startOffset = (self.parent.spritedata[2] & 0xF) * 22.5 + 90
        self.eventActivated = (self.parent.spritedata[4] & 0x40) != 0
        reversedDir = ((self.parent.spritedata[4] >> 4) & 1) != 0
        self.arcMiddleRotation = (self.parent.spritedata[4] & 0xF) * 22.5
        self.delay = self.parent.spritedata[6] & 0xF0
        self.arc = (self.parent.spritedata[7] >> 4) * 22.5
        self.rotationSpeed = ((self.parent.spritedata[7] & 0xF) / 0x800) * 360

        if reversedDir:
            self.startOffset += 180
        
        self.rotation = math.cos(math.radians(self.startOffset))
            
        self.aux[0].SetAngle(90 + self.arcMiddleRotation - self.arc * 0.5, self.arc)
        self.aux[1].SetAngle(90 + self.arcMiddleRotation - self.rotation * self.arc * 0.5, 0)

        super().dataChanged()

    def active(self):
        return not self.eventActivated

    def getStartRotation(self):
        if not self.eventActivated:
            self.rotation = math.cos(math.radians(self.startOffset - SLib.RotationFrame * self.rotationSpeed * (60 / SLib.RotationFPS)))

        return -self.arcMiddleRotation + self.rotation * self.arc * 0.5
    
class SpriteImage_ControllerSpinning_Universal(SLib.SpriteImage_MovementController):  # 118
    Speeds = [0x400000, 0x800000, 0xc00000, 0x1000000, 0x200000, 0x2000000, 0x4000000, 0x100000]

    def __init__(self, parent):
        super().__init__(
            parent,
            3.75,
            ImageCache['ControllerSpinning_Universal'],
        )
        self.aux.append(SLib.AuxiliaryRotationAreaOutline(parent, 60))
        self.aux.append(SLib.AuxiliaryRotationAreaOutline(parent, 120))
        self.xOffset = -8
        self.yOffset = -8
    @staticmethod
    def loadImages():
        SLib.loadIfNotInImageCache('ControllerSpinning_Universal', 'controller_spinning_universal.png')

    def dataChanged(self):
        self.rotation = (self.parent.spritedata[2] >> 4) * 22.5
        arc = (self.parent.spritedata[7] >> 4) * 22.5
        self.spinMode = self.parent.spritedata[3] & 3
        reversedDir = self.parent.spritedata[7] & 0xF > 7
        speedValue = self.parent.spritedata[7] & 0xF

        if speedValue > 7:
            speedValue -= 8

        self.rotationSpeed = (SpriteImage_ControllerSpinning_Shifting.Speeds[speedValue] / 0x100000000) * 360

        if reversedDir:
            self.rotation = -self.rotation
            self.rotationSpeed = -self.rotationSpeed

        if self.spinMode == 1:
            arc = 360

        self.aux[0].SetAngle(90 + self.rotation - (arc if reversedDir else 0), arc)
        self.aux[1].SetAngle(90 + self.rotation, 0)
        self.parent.updateScene()
        super().dataChanged()

    def active(self):
        return self.spinMode == 1

    def getStartRotation(self):
        if self.spinMode == 1:
            return -self.rotation - SLib.RotationFrame * self.rotationSpeed * (60 / SLib.RotationFPS)
        else:
            return -self.rotation

class SpriteImage_ControllerSwaying_Universal(SLib.SpriteImage_MovementController):  # 116
    def __init__(self, parent):
        super().__init__(
            parent,
            3.75,
            ImageCache['ControllerSwaying_Universal'],
        )

        self.aux.append(SLib.AuxiliaryRotationAreaOutline(parent, 60))
        self.aux.append(SLib.AuxiliaryRotationAreaOutline(parent, 120))

        self.rotation = 0
        self.startOffset = 0
        self.arc = 0
        self.eventActivated = False
        self.xOffset = -8
        self.yOffset = -8

    @staticmethod
    def loadImages():
        SLib.loadIfNotInImageCache('ControllerSwaying_Universal', 'controller_swaying_universal.png')

    def dataChanged(self):
        self.startOffset = (self.parent.spritedata[2] & 0xF) * 22.5 + 90
        self.eventActivated = (self.parent.spritedata[4] & 0x40) != 0
        reversedDir = ((self.parent.spritedata[4] >> 4) & 1) != 0
        self.arcMiddleRotation = (self.parent.spritedata[4] & 0xF) * 22.5
        self.delay = self.parent.spritedata[6] & 0xF0
        self.arc = (self.parent.spritedata[7] >> 4) * 22.5
        self.rotationSpeed = ((self.parent.spritedata[7] & 0xF) / 0x800) * 360

        if reversedDir:
            self.startOffset += 180
        
        self.rotation = math.cos(math.radians(self.startOffset))
            
        self.aux[0].SetAngle(90 + self.arcMiddleRotation - self.arc * 0.5, self.arc)
        self.aux[1].SetAngle(90 + self.arcMiddleRotation - self.rotation * self.arc * 0.5, 0)

        super().dataChanged()

    def active(self):
        return not self.eventActivated

    def getStartRotation(self):
        if not self.eventActivated:
            self.rotation = math.cos(math.radians(self.startOffset - SLib.RotationFrame * self.rotationSpeed * (60 / SLib.RotationFPS)))

        return -self.arcMiddleRotation + self.rotation * self.arc * 0.5

class SpriteImage_ControllerDancing(SLib.SpriteImage_StaticMultiple):
    def __init__(self, parent):
        super().__init__(
            parent,
            3.75,
            ImageCache['ControllerDancing'],
            (0, 0),
        )

    @staticmethod
    def loadImages():
        SLib.loadIfNotInImageCache('ControllerDancing', 'controller_dancing.png')

class SpriteImage_ControllerPath_Plus(SLib.SpriteImage_StaticMultiple):
    def __init__(self, parent):
        super().__init__(
            parent,
            3.75,
            ImageCache['ControllerPath_Plus'],
            (0, 0),
        )

    @staticmethod
    def loadImages():
        SLib.loadIfNotInImageCache('ControllerPath_Plus', 'controller_path_plus.png')

ImageClasses = {
    "railpolyp:odoriparent": SpriteImage_ControllerDancing,
    "railpolyp:swaydaenparent": SpriteImage_ControllerSwaying_Shifting,
    "railpolyp:daenparent": SpriteImage_ControllerSpinning_Shifting,
    "railpolyp:swaycentermp": SpriteImage_ControllerSwaying_Universal,
    "railpolyp:centermp": SpriteImage_ControllerSpinning_Universal,
    "railpolyp:railppp": SpriteImage_ControllerPath_Plus
}
