#include "GLTFSkin.h"
#include "GLTFNode.h"

#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

GLTF::Skin::Skin() {
	bindShapeMatrix = new float[16];
}

void GLTF::Skin::writeJSON(void* writer) {
	rapidjson::Writer<rapidjson::StringBuffer>* jsonWriter = (rapidjson::Writer<rapidjson::StringBuffer>*)writer;

	if (bindShapeMatrix != NULL) {
		jsonWriter->Key("bindShapeMatrix");
		jsonWriter->StartArray();
		for (int i = 0; i < 16; i++) {
			jsonWriter->Double(bindShapeMatrix[i]);
		}
		jsonWriter->EndArray();
	}
	if (inverseBindMatrices != NULL) {
		jsonWriter->Key("inverseBindMatrices");
		jsonWriter->String(inverseBindMatrices->id.c_str());
	}
	jsonWriter->Key("jointNames");
	jsonWriter->StartArray();
	for (GLTF::Node* node : joints) {
		if (node != NULL) {
			jsonWriter->String(node->id.c_str());
		}
	}
	jsonWriter->EndArray();
	GLTF::Object::writeJSON(writer);
}