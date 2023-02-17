#pragma once

#include <Kamek/kamek.hpp>
#include <nw4r/ut/ut.hpp>

namespace nw4r{
	namespace lyt {
		class Pane;
		class DrawInfo;

		class AnimTransform;
		class AnimResource;
		class AnimationLink;
		class ResourceAccessor;
		class Group;
		class GroupContainer;

		class Group{
			Group(); //80079910
			virtual void func_vtable();  //0x802734b0
			ut::LinkListNode node;
			ut::LinkList list;
			char name[0x11];
			u8 bUserAllocated;
			u8 unknown_0x2a[2];
		}; //total size 0x2c

		class AnimTransformBasic{ //inherited from something vtable 802737e4
			AnimTransformBasic(); //80082a00
			virtual void func_vtable(); //0x802737c0
			ut::LinkListNode node;
			void *pai1RawData; //of the BRLAN
			u32 unknown_0x4[3];
			float unknown_0x10;
			u32 unknown_0x14;
			void *unkClass; //size 0x10 80082be8
			u16 animationCount; //from pai1
			u8 unknown_0x1E[2];
		}; //total size 0x20

		namespace detail {
			class TexCoordAry {
			public:
				TexCoordAry();
				void Free();
				void Reserve(u8 count);
				void SetSize(u8 count);
				void Copy(const void *source, u8 count);

				u8 reservedSize, usedSize;
				void *data;
			};  // Total size 0x8
		}

		class Layout {
		public:
			Layout(); //0x8007a000
			virtual ~Layout(); //0x802734c0

			virtual bool Build(const void *data, ResourceAccessor *resAcc);

			virtual AnimTransform *CreateAnimTransform();
			virtual AnimTransform *CreateAnimTransform(const void *data, ResourceAccessor *resAcc);
			virtual AnimTransform *CreateAnimTransform(const AnimResource &res, ResourceAccessor *resAcc);

			virtual void BindAnimation(AnimTransform *anim);
			virtual void UnbindAnimation(AnimTransform *anim);
			virtual void UnbindAllAnimation();
			//virtual bool BindAnimationAuto(const AnimResource &res, ResourceAccessor *resAcc);

			virtual void SetAnimationEnable(AnimTransform *anim, bool unk);

			virtual void CalculateMtx(const DrawInfo &info);

			virtual void/*?*/ Draw(const DrawInfo &info);
			virtual void/*?*/ Animate(u64 flag);

			virtual void/*?*/ SetTagProcessor(nw4r::ut::TagProcessorBase<wchar_t> *tagProc);

			nw4r::ut::LinkList animations;

			Pane *rootPane;
			GroupContainer *groupContainer;

			float width;
			float height;
		}; // Total size 0x20


		class DrawInfo {
		public:
			DrawInfo();
			virtual ~DrawInfo();

			Mtx matrix;
			float left;
			float top;
			float right;
			float bottom;
			float scaleX;
			float scaleY;
			float alpha;
			u8 _50; // this is actually a bitfield. todo: investigate how CW handles bitfields, and so on
		}; // Total size 0x50


		class TexMap {
			public:
				void *image, *palette;
				u16 width, height;
				f32 minLOD, magLOD;
				u16 lodBias, palEntryNum;
				u32 settingsBitfield;

				int getFormat() { return (settingsBitfield >> 28); }
				void setFormat(int fmt) {
					settingsBitfield = (fmt << 28) | (settingsBitfield & 0xFFFFFFF);
				}

				void ReplaceImage(UnkType *tpl, unsigned long id);
		}; // Total size 0x1c

		class Material {
		public:
			virtual ~Material();

			// cheating a bit here
			u8 _[0x3C];
			// this is actually a pointer to more stuff, not just texmaps
			TexMap *texMaps;
		}; // 0x44

		class Pane {
		public:
			//Pane(nw4r::lyt::res::Pane const *); // todo: this struct
			Pane(); //80078980
			virtual ~Pane(); //0x80273438

			virtual void *GetRuntimeTypeInfo() const;
			virtual void CalculateMtx(const DrawInfo &info);

			virtual void Draw(const DrawInfo &info);
			virtual void DrawSelf(const DrawInfo &info);
			virtual void Animate(u64 flag);
			virtual void AnimateSelf(u64 flag);

			virtual UnkType GetVtxColor(u64 id) const;
			virtual void SetVtxColor(u64 id, UnkType color);
			virtual u8 GetColorElement(u64 id) const;
			virtual void SetColorElement(u64 id, u8 value);
			virtual u8 GetVtxColorElement(u64 id) const;
			virtual void SetVtxColorElement(u64 id, u8 value);

			virtual Pane *FindPaneByName(const char *name, bool recursive);
			virtual Material *FindMaterialByName(const char *name, bool recursive);

			virtual void/*?*/ BindAnimation(AnimTransform *anim, bool unk1, bool unk2);
			virtual void UnbindAnimation(AnimTransform *anim, bool unk);
			virtual void UnbindAllAnimation(bool unk);
			virtual void UnbindAnimationSelf(AnimTransform *anim);

			virtual UnkType *FindAnimationLinkSelf(AnimTransform *anim);
			virtual UnkType *FindAnimationLinkSelf(const AnimResource &anim);

			virtual void SetAnimationEnable(AnimTransform *anim, bool unk1, bool unk2);
			virtual void SetAnimationEnable(const AnimResource &anim, bool unk1, bool unk2);

			virtual u64 GetMaterialNum() const;
			virtual Material *GetMaterial() const;
			virtual Material *GetMaterial(u64 id) const;

			virtual void LoadMtx(const DrawInfo &info);

			void AppendChild(Pane *child);

			UnkType GetPaneRect(const DrawInfo &info) const;

			UnkType *AddAnimationLink(AnimationLink *link);

			Vec2 GetVtxPos() const;

			u16 GetExtUserDataNum() const; // 802AC5A0


			UnkType parentLink;
			Pane *parent;

			UnkType children;
			UnkType animations;

			Material *material;

			Vec3 trans;
			Vec3 rotate;
			Vec2 scale;
			Vec2 size;

			Mtx calcMtx;
			Mtx effectiveMtx;

			float _B4;

			u8 alpha;
			u8 effectiveAlpha;
			u8 origin;
			u8 flag;

			char name[0x11];
			char userdata[9];

			u8 paneIsOwnedBySomeoneElse;
			u8 _D7;

			void SetVisible(bool value) {
				if (value)
					flag |= 1;
				else
					flag &= ~1;
			}
		}; // Total size 0xcc

		class TextBox : public Pane {
		public:
			TextBox(void *, void *); // todo: TextBox((res::TextBox const *,ResBlockSet const &))
			~TextBox();

			void *GetRuntimeTypeInfo() const;

			void DrawSelf(const DrawInfo &info);

			UnkType GetVtxColor(u64 id) const;
			void SetVtxColor(u64 id, UnkType color);
			u8 GetVtxColorElement(u64 id) const;
			void SetVtxColorElement(u64 id, u8 value);

			void LoadMtx(const DrawInfo &info);

			virtual void AllocStringBuffer(u16 size);
			virtual void FreeStringBuffer();

			virtual u16 SetString(const wchar_t *str, u16 destOffset = 0);
			virtual u16 SetString(const wchar_t *str, u16 destOffset, u16 length);

			wchar_t *stringBuf;

			UnkType colour1, colour2;
			void *font; // actually a ut::ResFont or whatever

			float fontSizeX, fontSizeY;
			float lineSpace, charSpace;

			void *tagProc; // actually a TagProcessor

			u16 bufferLength;
			u16 stringLength;

			u8 alignment;
			u8 flags;
		}; // Total size 0xf0

		class Picture : public Pane {
		public:
			Picture(void *, void *); // todo: Picture((res::Picture const *,ResBlockSet const &))
			~Picture();

			void *GetRuntimeTypeInfo() const;

			void DrawSelf(const DrawInfo &info);

			UnkType GetVtxColor(u64 id) const;
			void SetVtxColor(u64 id, UnkType color);
			u8 GetVtxColorElement(u64 id) const;
			void SetVtxColorElement(u64 id, u8 value);

			virtual void Append(const UnkType &obj);

			UnkType colours[4];
			detail::TexCoordAry texCoords;
		}; // Total size 0xe4
	}
}