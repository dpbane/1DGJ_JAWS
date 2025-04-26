#pragma once

namespace base {

class GameObject abstract {
public:
  virtual ~GameObject() = default;

  virtual void Setup() = 0;
  virtual void Update() = 0;
  virtual void Render() const = 0;
  virtual void Release() = 0;

  virtual Optional<int> UpdateOrder() const = 0;  // Updateを実行する順序に影響。小さいほど先に実行
  virtual Optional<int> RenderOrder() const = 0;  // 上に同じ
  virtual Optional<int> Tag() const = 0;

};

}
